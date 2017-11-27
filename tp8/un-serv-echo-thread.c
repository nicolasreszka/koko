#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <string.h>

struct sockaddr_un {
  unsigned short sun_family;
  char sun_path[108];
};

void* serv(void* t){
  int* tab = (int*) t;
  close(tab[0]);
  char* buf;
  char tmp[108];
  int length;
 
  length = recv(tab[1], tmp, 108, 0);
  
  if(length == -1){
    perror("Problème avec recv");
    exit(-1);
  }
  
  buf = malloc(length);
  memset(buf, '\0', length);
  buf = tmp;
  
  send(tab[1], buf, length, 0);
}

int main(void){
  int fd, nfd, length, pid, tab[2];
  int yes = 1;
  socklen_t addr_size;
  char* buf;
  pthread_t th[3];

  struct sockaddr_un local;
  memset(&local, '\0', sizeof(struct sockaddr_un));
  local.sun_family = AF_UNIX;
  strcpy(local.sun_path, "/tmp/socket");

  fd = socket(AF_UNIX, SOCK_STREAM, 0);
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  if(fd == -1){
    perror("Problème avec socket");
    return EXIT_FAILURE;
  }

  unlink(local.sun_path);
  if(bind(fd, (struct sockaddr*) &local,
        sizeof(struct sockaddr_un)) == -1){
    perror("Problème avec bind");
    return EXIT_FAILURE;
  }

  if(listen(fd, 20) == -1){
    perror("Problème avec listen");
    return EXIT_FAILURE;
  }

  while(1){
    addr_size = sizeof(struct sockaddr_un);
    nfd = accept(fd, (struct sockaddr*) &local, &addr_size);

    if(nfd == -1){
      perror("Problème avec accept");
      return EXIT_FAILURE;
    }

    tab[0] = fd;
    tab[1] = nfd;

    pthread_create(&th[0], NULL, &serv, tab);

    pthread_join(th[0], NULL);

    close(nfd);
  }
}
