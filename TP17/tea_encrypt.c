#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
typedef unsigned uint128_t __attribute__ ((mode (TI)));

void encrypt (u_int32_t* v, u_int32_t* k) {
  u_int32_t delta = 0x9e3779b9;
  for (int i = 0; i < 32; i++) {
    v[0] += (v[1] * delta * i) ^ ((v[1] << 4) + k[0]) ^ ((v[1] >> 5) + k[1]);
    v[1] += (v[0] * delta * i) ^ ((v[0] << 4) + k[2]) ^ ((v[0] >> 5) + k[3]);
  }
}

void getKeyFromString(u_int32_t key[4], const char file_key_path[]){
  int fd_key = open(file_key_path, O_RDONLY, 0655); //RDONLY permissions are 0655
  if(fd_key == -1){
    perror("open");
    exit(errno);
  }
  int nb_bytes_read = read(fd_key, key, sizeof(__int128_t));
  if(nb_bytes_read == -1){
    perror("read");
    exit(errno);
  }
  if(nb_bytes_read != sizeof(__int128_t)){
    printf("Number bytes read from key file = %d, != 128 bits\n", nb_bytes_read);
    perror("read");
    errno = EIO;
    exit(errno);
  }
  return;
}

void encryptFile(const char file_to_encrypt_path[], u_int32_t key[4]){

  u_int32_t block[2];

  int nb_bytes_read = 0;
  int fd_to_encrypt = open(file_to_encrypt_path, O_RDONLY, 0655); //RDONLY permissions are 0655
  int fd_result_file = open("encrypted_file.dec", O_CREAT|O_TRUNC|O_WRONLY, 0666);


  while(1){
    memset(block, 0x0, sizeof(u_int64_t));

    nb_bytes_read = read(fd_to_encrypt, block, sizeof(u_int64_t));
    if(nb_bytes_read == -1){
      perror("read");
      exit(errno);
    }
    if(nb_bytes_read == 0){
      break; //EOF
    }
    encrypt(block, key);

    if(write(fd_result_file, block, sizeof(u_int64_t)) ==-1){
      perror("write");
      exit(errno);
    }
  }
}



int main(int argc, char const *argv[]) {
  if (argc < 3){
  		printf("usage : %s <file to encrypt> <file containing 128 bit key>\n", argv[0]);
  		exit(EXIT_FAILURE);
  }

  u_int32_t key[4];
  u_int32_t block[2];
  memset(key, 0x0, sizeof(u_int32_t) * 4);
  memset(block, 0x0, sizeof(u_int32_t) * 2);

  getKeyFromString(key, argv[2]);

  encryptFile(argv[1], key);

  return 0;
}
