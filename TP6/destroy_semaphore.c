#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun{
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *_buf;
} arg;


int main(int argc, char** argv) {
  key_t key1;
  key_t key2;
  key_t key3;
  if((key1 = ftok("/tmp",'1')) == -1){
    perror("ftok\n");
    exit(2);
  }
  if((key2 = ftok("/tmp",'2')) == -1){
    perror("ftok\n");
    exit(2);
  }
  if((key3 = ftok("/tmp",'3')) == -1){
    perror("ftok\n");
    exit(2);
  }
  int semid1 = semget(key1, 1, 0);
  int semid2 = semget(key2, 1, 0);
  int semid3 = semget(key3, 1, 0);
  semctl(semid1, 0, IPC_RMID);
  semctl(semid2, 0, IPC_RMID);
  semctl(semid3, 0, IPC_RMID);

  return 0;
}
