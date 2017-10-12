#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void third(int d){
  char tab[6] = {"third "};
  int i = 0;
  
  while(1){
    printf("%c",tab[i]);
    fflush(NULL);
    if(i < 5)
      i++;
    else
      i = 0;
    usleep(d);
  }
}

int main(int argc, char** argv){
  if(argc < 2){
    printf("Usage : %s <delay>\n", argv[0]);
    return EXIT_FAILURE;
  }

  third(atoi(argv[1]));

  return EXIT_SUCCESS;
}
