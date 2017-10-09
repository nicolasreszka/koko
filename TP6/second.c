#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


void second(int nsec){
  struct timespec tim;
     tim.tv_sec = 0;
     tim.tv_nsec = nsec * 1000000L;
  char first[7] = {'S', 'e', 'c', 'o', 'n', 'd', ' '};
  for(int i = 0; i < 7; i++){
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
  key_t key2;

  if((key3 = ftok("/tmp",'3')) == -1){
    perror("ftok\n");
    exit(2);
  }
  if((key2 = ftok("/tmp",'2')) == -1){
    perror("ftok\n");
    exit(2);
  }
  int semid3 = semget(key3, 1, 0);
  int semid2 = semget(key2, 1, 0);

  struct sembuf sem_in = {0, -1, 0};
  struct sembuf sem_out = {0, 1, 0};


  while(1){
    semop(semid2, &sem_in, 1);
    second(atoi(argv[1]));
    semop(semid3, &sem_out, 1);
  }
  return 0;
}
