#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void second(int d){
  char tab[7] = {"second "};
  int i = 0;
  
  while(1){
    printf("%c",tab[i]);
    fflush(NULL);
    if(i < 6)
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

  second(atoi(argv[1]));

  return EXIT_SUCCESS;
}
