#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

int main(void){
  int k,l;

  while(1){
    printf("Quel num de signal ?\n");
    scanf("%d", &k);
    printf("Quel processus ?\n");
    scanf("%d",&l);
    kill(l, k);
  }

  return EXIT_SUCCESS;
}
