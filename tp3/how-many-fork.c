#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
  int x, i = 0;
  char str[12];
  FILE* f = fopen("forks.txt","w");

  while(1){
    x = fork();
    
    if(x == -1){
    } else if( x == 0) {
      while(1);
    } else {
      i++;
      sprintf(str, "%d", i);
      fprintf(f, "%s\n", str);
    }
  }

  return EXIT_SUCCESS;
}
