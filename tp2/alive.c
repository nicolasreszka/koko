#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
  while(1){
    printf("PID = %d, I'm alive !\n",getpid());
    sleep(2);
  }

  return EXIT_SUCCESS;
}
