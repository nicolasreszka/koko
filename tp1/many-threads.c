#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<pthread.h>

pid_t gettid(void){
  return syscall(__NR_gettid);
}

void* func(void* arg){
  int* x = (int*) arg;
  while(1){
    printf("PID = %d, TID = %d, PTHID = %ul\n",
            getpid(),gettid(),pthread_self());
    printf("Thread number = %d\n",arg);
    sleep(5);
  }
}

int main(void){
  pthread_t th[3];
  int i = 0;

  for(i = 0; i < 3; i++){
    pthread_create(&th[i], NULL, &func,&i);
  }
  pthread_join(th[0], NULL);

  return EXIT_SUCCESS;
}
