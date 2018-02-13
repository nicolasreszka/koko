#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

#define BASE_DELTA 0x9e3779b9u
#define KEY_VALUE_HIGH 0x7A24432646294A40 //64bits value
#define KEY_VALUE_LOW 0x4E635266556A586E //64bits value

#define TEA_ROUNDS 64
#define KEY_SIZE 16


void decrypt (uint32_t* restrict v, const uint32_t* restrict k) {
  uint32_t delta = BASE_DELTA * 32;
  for (int i = 0; i < TEA_ROUNDS / 2 ; i++) {
    v[1] -= (v[0] + delta) ^ ((v[0] << 4) + k[2]) ^ ((v[0] >> 5) + k[3]);
    v[0] -= (v[1] + delta) ^ ((v[1] << 4) + k[0]) ^ ((v[1] >> 5) + k[1]);
    delta -= BASE_DELTA;
  }
}

void getKeyFromFile(const int fd_key, uint32_t key[4]){

  int nb_bytes_read = read(fd_key, key, KEY_SIZE);
  if(nb_bytes_read == -1){
    perror("read");
    exit(errno);
  }
  if(nb_bytes_read != KEY_SIZE){
    printf("Number bytes read from key file = %d, != 128 bits\n", nb_bytes_read);
    perror("read");
    errno = EIO;
    exit(errno);
  }
  return;
}

void decryptFile(const int fd, const uint32_t key[4]){

  uint32_t block[2];

  int nb_bytes_read = 0;

  int fd_result_file = open("decrypted_file.dec", O_CREAT|O_TRUNC|O_WRONLY, 0666);
  if(fd_result_file == -1){
    perror("open");
    exit(errno);
  }

  while(1){
    memset(block, 0x0, sizeof(block));

    nb_bytes_read = read(fd, block, sizeof(block));
    if(nb_bytes_read == -1){
      perror("read");
      exit(errno);
    }
    if(nb_bytes_read == 0){
      break; //EOF
    }
    decrypt(block, key);

    if(write(fd_result_file, block, sizeof(block)) ==-1){
      perror("write");
      exit(errno);
    }
  }
  close(fd);
  close(fd_result_file);
}



int main(int argc, char const *argv[]) {
  if (argc < 3){
  		printf("usage : %s <file to encrypt> <file containing 128 bit key>\n", argv[0]);
  		exit(EXIT_FAILURE);
  }

  uint32_t key[4];
  u_int32_t block[2];
  memset(key, 0x0, sizeof(uint32_t) * 4);
  memset(block, 0x0, sizeof(uint32_t) * 2);

  //Note that __uint128_t requiers gcc version > 4.4
  __uint128_t key_val = ((__uint128_t) KEY_VALUE_HIGH << 64 | (__uint128_t) KEY_VALUE_LOW);
  key[0] = key_val >> 0;
  key[1] = key_val >> 32;
  key[2] = key_val >> 64;
  key[3] = key_val >> 96;

  int fd = open(argv[2], O_RDONLY, 0655); //RDONLY permissions are 0655
  if(fd == -1){
    perror("open");
    exit(errno);
  }

  getKeyFromFile(fd, key);

  decryptFile(fd, key);

  return EXIT_SUCCESS;
}
