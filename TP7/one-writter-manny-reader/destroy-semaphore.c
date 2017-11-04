
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#define SHARED_MOMORY_SIZE 4

union semun{
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *_buf;
} arg;

int main(int argc, char const *argv[]) {
  key_t key;

  if((key = ftok("/tmp",'a')) == -1){
    perror("ftok");
    exit(2);
  }

  int semid1 = semget(key, 1, 0);

  semctl(semid1, 0, IPC_RMID);



  int key_valeur;
  if( (key_valeur = ftok("/tmp", 'c') ) == -1){
    perror("ftok error key c\n");
    exit(-1);
  }

  int shmid3;
  if( (shmid3 = shmget(key_valeur, SHARED_MOMORY_SIZE, 0)) == -1){
    perror("shmget error\n");
    exit(-2);
  }
  if(shmctl(shmid3, IPC_RMID, NULL) == -1){
    perror("shmctl error");
    exit(-3);
  }



  return 0;
}
