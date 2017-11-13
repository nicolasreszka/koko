#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/socket.h"
#include "sys/un.h"

#define MESSAGE_SIZE 109

void sigchild_handler(int signal) {
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("usage : %s <chemin du fichier>\n", argv[0]);
		return EXIT_FAILURE;
	}	

	struct sigaction sa;
	sa.sa_handler = &sigchild_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	socklen_t sockaddr_un_size;
	sockaddr_un_size = sizeof(struct sockaddr_un);

	struct sockaddr_un local;
	memset(&local, 0, sizeof(struct sockaddr_un));
	local.sun_family = AF_UNIX;
	strncpy(local.sun_path, argv[1], 108);

	int socket_id, yes, nid, pid;
	char message[MESSAGE_SIZE];

	socket_id=socket(AF_UNIX,SOCK_STREAM,0);
	if (socket_id < 0) {
		perror("socket");
	}

	yes = 1;
	if(setsockopt(socket_id,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) < 0) {
		perror("setsockopt");
	}

	if (bind(socket_id, (struct sockaddr*)&local, sizeof(local)) < 0) {
		perror("bind");
	}

	if (listen(socket_id, 0) < 0) {
		perror("listen");
	}

	while (1) {
		nid=accept(socket_id, (struct sockaddr*)&local, &sockaddr_un_size);
		if (nid < 0) {
			perror("nid");
		}

		pid = fork();
		if (pid == -1) {
			perror("fork");
		}
		if (pid == 0) {
			close(socket_id);
			if (recv(nid,message,MESSAGE_SIZE, MSG_WAITALL) < 0) {
				perror("recv");
			} else {
				printf("%s\n",message);
				if (send(nid,message,MESSAGE_SIZE, MSG_EOR) < 0) {
					perror("send");
				}
			}
			exit(0);
		}
		close(nid);
	}

	return EXIT_SUCCESS;
}