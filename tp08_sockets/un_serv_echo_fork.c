/*	Ce programme execute un serveur Unix Domain dont les coordonnées 
	sont passées sur la ligne de commande, qui attend un client, 
	réceptionne ce que le client envoie et renvoie la même chose au 
	client en créant un processus */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/socket.h"

/* Ce header contient la structure sockaddr_un */
#include "sys/un.h" 

/* La longueur maximale du message transmis */
#define MESSAGE_SIZE 109

/* Le nombre maximal de clients */
#define MAX_CLIENTS 20


/* Pour s'occuper de zombies (voir TP1) */
void sigchild_handler(int signal) {
	while(waitpid(-1, NULL, WNOHANG) > 0);
}


int main(int argc, char** argv) {

	if (argc < 2) {
		printf("usage : %s <chemin du fichier>\n", argv[0]);
		return EXIT_FAILURE;
	}	

	/* 	On déclare et initialise la structure
		qui contiendra le path pour accéder
		au fichier lié au socket "sun_path"
		et le domaine de communication du socket "sun_family" */
	struct sockaddr_un local;

	/* On libère la mémoire à l'emplacement de la structure */
	memset(&local, 0, sizeof(struct sockaddr_un));

	/* Domaine du socket */
	local.sun_family = AF_UNIX;

	/* Emplacement du socket, récupéré depuis la ligne de commande, 
	   (108 caractères pour des raisons historiques) */
	strncpy(local.sun_path, argv[1], 108);

	/* Pour s'occuper de zombies (voir TP1) */
	struct sigaction sa;
	sa.sa_handler = &sigchild_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	/* Initialisation des variables qui serviront à s'occuper des éventuelles erreurs*/
	int setsockopt_result, bind_result, listen_result, send_result, recv_result;

	/* Initialisation des variables qui vont contenir les identifiants */
	int socket_fd, nid, pid;

	/* On en aura besoin pour setsockopt()*/
	int yes = 1;

	/* On aura besoin de cette variable pour la fonction accept() */
	socklen_t sockaddr_un_size;
	sockaddr_un_size = sizeof(struct sockaddr_un);

	/* Chaîne de caractères du message */
	char message[MESSAGE_SIZE];
	memset(message, '\0', MESSAGE_SIZE);


	/* int socket(int domain, int type, int protocol);
	 *
	 * Cette fonction crée un point d'accès pour la communication et
	 * renvoie un déscripteur de fichier.
	 *
	 * Arguments : 
	 *	- domain : AF_UNIX car on veut une communication locale
	 *	- type : SOCK_STREAM pour un flux de données
	 *	- protocol : 0 pour le protocol par défaut
	*/ 
	socket_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if (socket_fd == -1) {
		perror("socket");
	}


	/*  int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
	 *
	 * Manipulation des options pour le socket
	 *
	 * Arguments : 
	 *	- sockfd : le descripteur de fichier du socket
	 *	- level : SOL_SOCKET pour manipuler les options au niveau du socket
	 *	- optname : SO_REUSEADDR pour la réutilisation d'adresse
	 *	- optval : il faut passer le pointeur de la variable dans la fonction
	 *	- optlen : la longeur de l'opération (ici 4 octets)
	*/ 
	setsockopt_result = setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
	if(setsockopt_result == -1) {
		perror("setsockopt");
	}

	/*	On unlink le path du socket, au cas où
		il serait déjà attribué */
	unlink(local.sun_path);


	/* On associe l'addresse du socket à son déscripteur */
	bind_result = bind(socket_fd, (struct sockaddr*)&local, sizeof(local));
	if (bind_result == -1) {
		perror("bind");
	}


	/*	On change le mode de connexion du socket pour
   		commencer à écouter et créer une file
   		de connexion si le nb de demandes
   		dépasse la capacité maximale */
	listen_result = listen(socket_fd, MAX_CLIENTS);
	if (bind_result == -1) {
		perror("listen");
	}

	while (1) {
		/*	Extrait la demande de connexion en tête de file
			au socket socket_fd, crée un nouveau socket connecté,
			puis retourne un nouveau FD vers ce socket.
			Le nouveau socket n'est pas en étant d'écoute 
			et le socket socket_fd n'est pas affecté par cet appel */
		nid = accept(socket_fd, (struct sockaddr*)&local, &sockaddr_un_size);
		if (nid == -1) {
			perror("nid");
		}

		pid = fork();
		if (pid == -1) {
			perror("fork");
		}

		/* Création d'un processus qui gère la réception et le renvoi des données*/
		if (pid == 0) {
			close(socket_fd);

			/* Lecture */
			recv_result = recv(nid,message,MESSAGE_SIZE, MSG_WAITALL);
			if (recv_result == -1) {
				perror("recv");
			} else {
				printf("%s\n",message);

				/* Ecriture */
				send_result = send(nid,message,MESSAGE_SIZE, MSG_EOR);
				if (send_result == -1) {
					perror("send");
				}
			}
			exit(0);
		}

		if (pid > 0) {
			close(nid);
		}
	}

	return EXIT_SUCCESS;
}