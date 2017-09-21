#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
  int x = fork();

  if(x == -1) {
    perror("Problème avec fork\n");
    return EXIT_FAILURE;
  } else  if(x == 0){
    printf("Hello, I'm the son\n");
    printf("PID = %d\n",getpid());
    printf("Group id = %d\n",getpgid(getpid()));
    printf("Session id = %d\n",getsid(getpid()));
  } else if (x > 1) {
    printf("Hello, i'm the father. My PID is %d\n",getpid());
  }

  return EXIT_SUCCESS;
}
