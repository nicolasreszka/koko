#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void){

  int x;
  //Label:
  x = fork();
  if(x == -1){
    perror("Couldn't fork\n");
    exit(1);
  } if (x == 0){
    //child
    printf("PID fils : %d\n", getpid());

    while(1){
      sleep(5);
    }
  } if (x > 0){
    //father
    printf("PID père : %d\n", getpid());

    //goto Label;
    while(1){
      sleep(5);
    }
  }

  return EXIT_SUCCESS;
}
