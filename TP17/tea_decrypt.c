#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BASE_DELTA 0x9e3779b9

u_int32_t delta = BASE_DELTA;

void decrypt (u_int32_t* v, u_int32_t* k) {

  for (int i = 32 - 1; i >= 0 ; i--) {
    v[1] -= (v[0] * delta * i) ^ ((v[0] << 4) + k[2]) ^ ((v[0] >> 5) + k[3]);
    v[0] -= (v[1] * delta * i) ^ ((v[1] << 4) + k[0]) ^ ((v[1] >> 5) + k[1]);
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
  close(fd_key);
  return;
}

void decryptFile(const char file_to_decrypt_path[], u_int32_t key[4]){

  u_int32_t block[2];

  int nb_bytes_read = 0;
  int fd_to_decrypt = open(file_to_decrypt_path, O_RDONLY, 0655); //RDONLY permissions are 0655
  int fd_result_file = open("decrypted_file.dec", O_CREAT|O_TRUNC|O_WRONLY, 0666);

  while(1){
    memset(block, 0x0, sizeof(u_int64_t));

    nb_bytes_read = read(fd_to_decrypt, block, sizeof(u_int64_t));
    if(nb_bytes_read == -1){
      perror("read");
      exit(errno);
    }
    if(nb_bytes_read == 0){
      break; //EOF
    }
    decrypt(block, key);

    if(write(fd_result_file, block, sizeof(u_int64_t)) ==-1){
      perror("write");
      exit(errno);
    }
  }
  close(fd_to_decrypt);
  close(fd_result_file);

}



int main(int argc, char const *argv[]) {

  if (argc < 3){
  		printf("usage : %s <file to decrypt> <file containing 128 bit key>\n", argv[0]);
  		exit(EXIT_FAILURE);
  }

  u_int32_t key[4];
  u_int32_t block[2];
  memset(key, 0x0, sizeof(u_int32_t) * 4);
  memset(block, 0x0, sizeof(u_int32_t) * 2);

  getKeyFromString(key, argv[2]);

  decryptFile(argv[1], key);

  return 0;
}
