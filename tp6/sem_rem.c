#include<stdlib.h>
#include<sys/sem.h>

int main(void){
  key_t key = ftok("/tmp", 'a');
  int semid = semget(key, 3, 0666|IPC_CREAT|IPC_EXCL);

  semctl(semid, 0, IPC_RMID);
  return EXIT_SUCCESS;
}
