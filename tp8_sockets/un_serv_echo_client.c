/*	Ce programme execute un client Unix Domain qui se connecte 
	à un serveur dont les coordonnées sont passées sur la ligne 
	de commande, envoie un message, puis reçoit ce même message */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/socket.h"
#include "sys/un.h"

#define MESSAGE_SIZE 109

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("usage : %s <chemin du fichier>\n", argv[0]);
		return EXIT_FAILURE;
	}	

	/* (Voir un_serv_echo_fork.c) */
	struct sockaddr_un local;
	memset(&local, 0, sizeof(struct sockaddr_un));
	local.sun_family = AF_UNIX;
	strncpy(local.sun_path, argv[1], 108);


	int read_result, send_result, recv_result;

	socklen_t sockaddr_un_size;
	sockaddr_un_size = sizeof(struct sockaddr_un);

	int socket_fd, pid;
	char message[MESSAGE_SIZE];
	
	while(1) {
		/* Initialisation de la mémoire */
		memset(message, '\0', MESSAGE_SIZE);

		/* Création du socket */
		socket_fd=socket(AF_UNIX,SOCK_STREAM,0);
		if (socket_fd < 0) {
			perror("socket");
		}

		/* Connexion au serveur */
		if (connect(socket_fd, (struct sockaddr*)&local, sockaddr_un_size) < 0) {
			perror("connect");
		}

		/* Ecriture du message */
		printf("message ?\n");
		read_result = read(0,message,MESSAGE_SIZE);
		
		if (read_result == -1) {
			perror("read");
		} else {

			/* Envoi */
			send_result = send(socket_fd,message,MESSAGE_SIZE,0);
			if (send_result == -1) {
				perror("send");
			} else {

				/* Réception */
				recv_result = recv(socket_fd,message,MESSAGE_SIZE, MSG_WAITALL);
				if (recv_result == -1) {
					perror("recv");
				} else {
					printf("response : %s\n", message);
				} 
			}
		}		
		close(socket_fd);
	}
	
	return EXIT_SUCCESS;
}
