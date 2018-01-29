#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BLOCK_SIZE 2048
#define FILE_TO_RECOVER_SIZE (BLOCK_SIZE * 11)

/*
BLOCKS:
(0-10):14689-14699
TOTAL: 11
*/


#define BLOCK_TO_READ_FROM 14689
#define NB_BLOCKS_TO_READ 11

int main(int argc, char const *argv[]) {
  int inode_number = -1;
  int file_size = FILE_TO_RECOVER_SIZE;
  int buff[BLOCK_SIZE];
  int fd = open("/tmp/image.ext3", O_RDONLY, 0655);
  int fd_write = open("./image.jpg", O_WRONLY|O_CREAT|O_TRUNC, 0665);

  if(lseek(fd, BLOCK_SIZE * 14689, SEEK_SET) == -1){
      perror("lseek");
      exit(errno);
  }

  if(fd == -1){
    perror("open");
    exit(errno);
  }

  int y = -1;
  int w = -1;
  for(int i = 0; i < NB_BLOCKS_TO_READ; i++){
      memset(buff, 0x0, BLOCK_SIZE);
      y = read(fd, &buff, BLOCK_SIZE);
      if(y == -1){
        perror("read");
        exit(errno);
      }
      w = write(fd_write, &buff, BLOCK_SIZE);
      if(w == -1){
        perror("write");
        exit(errno);
      }
  }

  return 0;
}
