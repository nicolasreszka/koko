#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char** argv){
  int id, nid, pid, yes = 1, fd;
  int length;
  socklen_t addr_size;
  char* buf;
  char* answr;

  if(argc < 3){
    printf("Usage : %s <file name> <IPv4 addr>", argv[0]);
    return EXIT_FAILURE;
  }

  /* Init de la structure */

  struct sockaddr_in local;
  memset(&local, '\0', sizeof(struct sockaddr_in));
  local.sin_family = AF_INET;
  local.sin_port = htons((unsigned short) strtol(argv[2], NULL, 0));
  local.sin_addr.s_addr = INADDR_ANY;

  /* Init du socket */
  
  id = socket(AF_INET, SOCK_DGRAM, 0);

  if(id == -1){
    perror("Problème socket");
    return EXIT_FAILURE;
  }
  
  setsockopt(id, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  /* Liaison du socket */

  if(bind(fd, (struct sockaddr*) &local,
        sizeof(struct sockaddr_in)) == -1){
    perror("Problème avec bind");
    return EXIT_FAILURE;
  }

  /* Ecoute du socket */
  if(listen(id, 20) == -1){
    perror("Problème avec listen");
    return EXIT_FAILURE;
  }

  /* Accept / boucle */
  
  buf = (char*) malloc(sizeof(char) * 50); /* Nombre choisi arbitrairement */
  memset(buf, '\0', 50);

  while(buf != "end"){
    addr_size = sizeof(struct sockaddr_in);
    nid = accept(id, (struct sockaddr*) &local, &addr_size);

    if(nid == -1){
      perror("Problème avec accept");
      return EXIT_FAILURE;
    }

    pid = fork();

    if(pid == -1){
      perror("Problème avec fork");
      return EXIT_FAILURE;
    } else {
      close(id);

      int fd;

      fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0666);
      while(1){
        if(length == 0)
          break;
        else if(length == -1){
          perror("Problème write");
          return EXIT_FAILURE;
        }

        memset(buf, '\0', 50);
        length = recvfrom(nid, buf, 50, 0, NULL, NULL);

        if(length == -1){
          perror("Problème recv");
          return EXIT_FAILURE;
        } 

        length = write(fd, buf, 50);
        
        memset(buf, '\0', 50);
        strcpy(buf, "next");

        sendto(nid, buf, 50, 0, 
            (struct sockaddr*) &local, sizeof(local));
      }
      close(nid);
      return EXIT_SUCCESS;
    }

    if(pid > 0){
      close(nid);
    }
  }

  /* Close du socket */
  
  close(id);

  return EXIT_SUCCESS;
}
