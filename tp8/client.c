#include <sys/socket.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>

int main(int argc, char const *argv[]) {
  int id = socket(AF_UNIX, SOCK_STREAM ,0);
  if(id == -1){
    perror("socket");
    exit(-1);
  }
  char sun_path_user[108];
  memset(sun_path_user, '\0', 108);
  strcpy(sun_path_user, "/tmp/socket");

  struct sockaddr_un local_adress;
  local_adress.sun_family = AF_UNIX;
  strcpy(local_adress.sun_path, sun_path_user);

  if(connect(id, (struct sockaddr *)&local_adress, sizeof(struct sockaddr_un)) == -1){
    perror("connect");
    exit(-1);
  }
  char message[20] = "Message";
  if(send(id, message, sizeof(message), 0) == -1){
    perror("send");
    exit(-1);
  }
  if(recv(id, message, sizeof(message), 0) == -1){
    perror("recv");
    exit(-1);
  }
  printf("<%d> RECEIVED MESSAGE = %s \n", getpid(), message);

  return 0;
}
