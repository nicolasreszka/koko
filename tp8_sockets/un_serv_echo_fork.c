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
	int setsockopt_result, bind_result, listen_result, send_result, recv_result;

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
	memset(message, '\0', MESSAGE_SIZE);

	socket_id = socket(AF_UNIX,SOCK_STREAM,0);
	if (socket_id == -1) {
		perror("socket");
	}

	yes = 1;
	setsockopt_result = setsockopt(socket_id,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
	if(setsockopt_result == -1) {
		perror("setsockopt");
	}

	bind_result = bind(socket_id, (struct sockaddr*)&local, sizeof(local));
	if (bind_result == -1) {
		perror("bind");
	}

	listen_result = listen(socket_id, 0);
	if (bind_result == -1) {
		perror("listen");
	}

	while (1) {
		nid=accept(socket_id, (struct sockaddr*)&local, &sockaddr_un_size);
		if (nid == -1) {
			perror("nid");
		}

		pid = fork();
		if (pid == -1) {
			perror("fork");
		}

		if (pid == 0) {
			close(socket_id);
			recv_result = recv(nid,message,MESSAGE_SIZE, MSG_WAITALL);
			if (recv_result == -1) {
				perror("recv");
			} else {
				printf("%s\n",message);
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