#define SHARED_MOMORY_SIZE 4
#define NB_WRITER 1
#define NB_READER 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


int* valeur;

void reader(int semid){

  struct sembuf sem_in = {0, -1, 0};
  struct sembuf sem_out = {0, 1, 0};
  printf("HELLO MABITE\n");
  while(1){
    semop(semid, &sem_in, 1); //ON effectue l'opé sem_in (ici, on lock)
    usleep(100000);
    printf("\t reader %d: shval %d\n", getpid(), *valeur);
    semop(semid, &sem_out, 1); //Opé sem_out (delock)
  }

}


void writer(int semid){


  struct sembuf sem_in = {0, -1, 0};
  struct sembuf sem_out = {0, 1, 0};
  printf("HELLO CHICHA\n");
  while(1){

    semop(semid, &sem_in, 1); //ON effectue l'opé sem_in (ici, on lock)
    *valeur = *valeur+1;
    usleep(2000000);
    *valeur = *valeur+1;
    printf("writter\t %d: shval = %d\n", getpid(), *valeur);
    semop(semid, &sem_out, 1); //Opé sem_out (delock)
    usleep(2000000);
  }
  return;
}

int main(int argc, char const *argv[]) {
  int key_valeur;
  int key_sem;
  int shmid;

  /* On récupère la valeur
   *
  */
  if( (key_valeur = ftok("/tmp", 'c') ) == -1){
    perror("ftok error key c\n");
    exit(-1);
  }

  if( (shmid = shmget(key_valeur, SHARED_MOMORY_SIZE, 0)) == -1){
    perror("semget");
    exit(-1);
  }

  valeur = (int*)shmat(shmid, NULL, 0);
  /* On récupère le sémaphore
   *
  */

  if((key_sem = ftok("/tmp",'a')) == -1){
    perror("ftok");
    exit(2);
  }

  int semid = semget(key_sem, 1, 0);

  for(int i = 0; i < NB_WRITER; i++){
    int pid;
    pid = fork();
    /*erreur*/
    if(pid == -1){
      perror("fork");
      exit(-42);
    }
    /*Code du fils*/
    if(pid == 0){
      writer(semid);
      //exit(1);
    }
  }

  for(int i = 0; i < NB_READER; i++){
    int pid;
    pid = fork();
    if(pid == -1){
      perror("fork");
      exit(-42);
    }
    /*Code du fils*/
    if(pid == 0){
      reader(semid);
      //exit(1);
    }

  }

  return 0;
}
