#include<stdlib.h>
#include<sys/sem.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int* array;
  struct seminfo *_buf;
} arg;

int main(void){
  key_t key = ftok("/tmp", 'a');
  int semid = semget(key, 3, 0666|IPC_CREAT|IPC_EXCL);
  arg.val = 1;
  struct sembuf open[2] = {{0, 1, 0}, {0, -1, 0}};
  semctl(semid, 0, SETVAL, arg);
  semctl(semid, 1, SETVAL, 0);
  semctl(semid, 2, SETVAL, 0);

  return EXIT_SUCCESS;
}
