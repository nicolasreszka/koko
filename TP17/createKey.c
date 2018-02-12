#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define KEY_VALUE 0x7A24432646294A404E635266556A586E //128bits value

int main(int argc, char const *argv[]) {
  u_int32_t key[4];
  __uint128_t key_val = KEY_VALUE;
  *key = key_val;
  int key_file = open("key.dat", O_CREAT|O_TRUNC|O_WRONLY, 0666);
  if(key_file == -1){
    perror("open");
    exit(errno);
  }
  if((write(key_file, key, sizeof(__int128))) == -1){
    perror("write");
    exit(errno);
  }

  return 0;
}
