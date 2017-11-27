#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_LENGTH 50

struct sockaddr_un {
  unsigned short sun_family; /* AF_UNIX */
  char sun_path[108];
};

int main(int argc, char** argv){
  int sfd, nid, pid, length;
  socklen_t addr_size;
  char* buf;

  if(argc < 2){
    perror("Usage : %s <file name>");
    return EXIT_FAILURE;
  }

  /* On déclare et initialise la structure
   * qui contiendra le path pour accéder
   * au fichier lié au socket "sun_path"
   * et le domaine de communication du socket "sun_family" */
  struct sockaddr_un local;
  memset(&local, '\0', sizeof(struct sockaddr_un)); /* Reset de la mémoire */
  local.sun_family = AF_UNIX; /* Domaine du socket */
  /* Path du socket, pris sur la ligne de commande */
  strncpy(local.sun_path, argv[1], 108);

  /* Création du FD d'un socket du type
   * SOCK_DGRAM, qui fournit des datagrammes
   * en mode hors connexion*/
  sfd = socket(AF_UNIX, SOCK_DGRAM, 0);

  if(sfd == -1){
    perror("Problème avec socket");
    return EXIT_FAILURE;
  }

  /* On unlink le path du socket, au cas où
   * il serait déjà bind */
  unlink(local.sun_path);
  /* On associe l'addresse du socket à son file descriptor */
  if(bind(sfd, (struct sockaddr*) &local, 
        sizeof(struct sockaddr_un)) == -1){
    perror("Problème bind");
    return EXIT_FAILURE;
  }

  /* Change le mode de connexion de socket pour
   * commencer à l'écouter et créer une file
   * de connexion si le nb de demandes
   * dépasse 20 */
  if(listen(sfd, 20) == -1){
    perror("Problème avec listen");
    return EXIT_FAILURE;
  }

  while(1){
    addr_size = sizeof(struct sockaddr_un);
    /* Extrait la demande de connexion en tête de file
     * au socket sfd, crée un nouveau socket connecté,
     * puis retourne un nouveau FD vers ce socket.
     * Le nouveau socket n'est pas en étant d'écoute 
     * et le socket sfd n'est pas affecté par cet appel */
    nid = accept(sfd, (struct sockaddr*) &local, &addr_size);

    if(nid == -1){
      perror("Problème avec accept");
      return EXIT_FAILURE;
    }

    /* J'vous laisse deviner à quoi ça sert */
    pid = fork();

    if(pid == -1){
      perror("Problème fork");
      return EXIT_FAILURE;
    } else if (pid > 0) {
      wait(NULL);
    } else {
      close(sfd);
      /* On prépare le buffer qui va recevoir
       * le message venant du nouveau socket */
      buf = malloc(MSG_LENGTH);
      memset(buf, '\0', MSG_LENGTH);
      /* On lit un message sur le socket de 50 octets max */
      length = recv(nid, buf, MSG_LENGTH, 0);

      if(length == -1){
        perror("Problème avec recv");
        return EXIT_FAILURE;
      }

      /* On renvoie le message lu sur le socket */
      send(nid, buf, length, 0);
    }

    close(nid);
  }

  return EXIT_SUCCESS;
}
