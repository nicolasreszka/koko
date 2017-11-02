
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
  key_t key_writer;

  if((key_writer = ftok("/tmp",'a')) == -1){
    perror("ftok");
    exit(2);
  }


  //reader 0
  //writer 1

  int semid1 = semget(key_writer, 1, 0666|IPC_CREAT|IPC_EXCL);

  arg.val = 1;
  semctl(semid1, 0, SETVAL, arg);


  int key_valeur;
  if( (key_valeur = ftok("/tmp", 'c') ) == -1){
    perror("ftok error key c\n");
    exit(-1);
  }

  int shmid3;
  if( (shmid3 = shmget(key_valeur, SHARED_MOMORY_SIZE, 0666|IPC_CREAT|IPC_EXCL)) == -1){
    perror("shmget error key_compteur\n");
    exit(-2);
  }

  int* valeur = (int*)shmat(shmid3, NULL, 0);
  *valeur = 0;


  return 0;
}
