#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


void third(int nsec){
  struct timespec tim;
     tim.tv_sec = 0;
     tim.tv_nsec = nsec * 1000000L;
  char first[6] = {'T', 'h', 'i', 'r', 'd', ' '};
  for(int i = 0; i < 6; i++){
    printf("%c", first[i]);
    fflush(stdout);
    if(nanosleep(&tim , NULL) < 0)
     {
        printf("Nano sleep system call failed \n");
        return;
     }
  }
}

int main(int argc, char ** argv) {
  if(argc != 2){
    perror("Usage : <time MSEC>\n");
    exit(1);
  }
  key_t key3;
  key_t key1;

  if((key3 = ftok("/tmp",'3')) == -1){
    perror("ftok\n");
    exit(2);
  }
  if((key1 = ftok("/tmp",'1')) == -1){
    perror("ftok\n");
    exit(2);
  }
  int semid3 = semget(key3, 1, 0);
  int semid1 = semget(key1, 1, 0);

  struct sembuf sem_in = {0, -1, 0};
  struct sembuf sem_out = {0, 1, 0};


  while(1){
    semop(semid3, &sem_in, 1);
    third(atoi(argv[1]));
    semop(semid1, &sem_out, 1);
  }
  return 0;
}
