#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#define VMAX 5
#define NB_INCR_THREADS 3
#define NB_RESET_THREADS 1

pthread_cond_t cond_reset = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_inc = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int valeur_commune = 0;


void* incr_routine(void * thread_number){
  int i = *(int*) thread_number;
  i += 1;

  while (1) {
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 500 * 1000000L;
    pthread_mutex_lock(&lock);

    if(valeur_commune < 5) {
      printf("inc%d : before x=%d\n", i, valeur_commune);
      valeur_commune++;
      printf("\t after x=%d\n", valeur_commune);
    }
    if(valeur_commune == 5){
      pthread_cond_signal(&cond_reset);
      pthread_cond_wait(&cond_inc, &lock);
    }

    pthread_mutex_unlock(&lock);
    nanosleep(&tim, NULL);
  }

  pthread_exit(NULL);
}

void* reset_routine(void * thread_number){
  int i = *(int*) thread_number;
  struct timespec tim;
  tim.tv_sec = 0;
  tim.tv_nsec = 200 * 1000000L;
  while(1){
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond_reset, &lock);

    printf("reset%d : before x=%d\n", i, valeur_commune);
    if(valeur_commune >= VMAX){
      valeur_commune = 0;
    }
    printf("\t after x=%d\n", valeur_commune);
    pthread_cond_signal(&cond_inc);
    pthread_mutex_unlock(&lock);
    nanosleep(&tim, NULL);
  }


  pthread_exit(NULL);
}

int main (void){

  pthread_t threads_inc[NB_INCR_THREADS];
  pthread_t threads_reset[NB_RESET_THREADS];

    for(int i = 0; i < NB_INCR_THREADS; i++){
      printf("-----this is incr%d-----\n", i+1);
      pthread_create(&threads_inc[i], NULL, incr_routine, (void*)&i);
      //pthread_join(threads_inc[i], NULL);
    }
    for(int i = 0; i < NB_RESET_THREADS; i++){
      printf("=====this is reset%d=====\n", i+1);
      pthread_create(&threads_reset[i], NULL, reset_routine, (void*)&i);
      //pthread_join(threads_reset[i], NULL);
    }
  while (1) {
    /* code */
  }


  return EXIT_SUCCESS;
}
