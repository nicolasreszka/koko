#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/socket.h"
#include "sys/un.h"
#include "sys/syscall.h"

#define MESSAGE_SIZE 109

char message[MESSAGE_SIZE];

void* client_routine(void *arg_nid) {
	int nid, recv_result, send_result;
   	
   	nid = *(int*) arg_nid; 
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

	pthread_exit(NULL);
}

void create_thread(int *nid) {
	pthread_t thread;
	pthread_create(&thread, NULL, client_routine, (void*)nid); 
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("usage : %s <chemin du fichier>\n", argv[0]);
		return EXIT_FAILURE;
	}	
	int setsockopt_result, bind_result, listen_result;

	socklen_t sockaddr_un_size;
	sockaddr_un_size = sizeof(struct sockaddr_un);

	struct sockaddr_un local;
	memset(&local, 0, sizeof(struct sockaddr_un));
	local.sun_family = AF_UNIX;
	strncpy(local.sun_path, argv[1], 108);

	int socket_id, yes, nid, pid;
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

		create_thread(&nid);

		close(nid);	
	}

	return EXIT_SUCCESS;
}