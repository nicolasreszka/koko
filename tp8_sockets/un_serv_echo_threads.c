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
#define MAX_CLIENTS 16


char message[MESSAGE_SIZE];

typedef struct client_thread_structure {
    pthread_t thread;
    int is_free;
} client_thread;

typedef struct client_thread_args_structure {
    int thread_number;
    int* nid;
} client_thread_args;

client_thread client_threads[MAX_CLIENTS];

void* client_routine(void *args) {
	client_thread_args* args_casted;
	int thread_number, nid, recv_result, send_result;
   	
	args_casted = (client_thread_args*) args;
   	nid = *args_casted->nid;
   	thread_number = args_casted->thread_number;

   	recv_result = recv(*args_casted->nid,message,MESSAGE_SIZE, MSG_WAITALL);
	
	if (recv_result == -1) {
		perror("recv");
	} else {
		printf("%s\n",message);
		send_result = send(*args_casted->nid,message,MESSAGE_SIZE, MSG_EOR);
		if (send_result == -1) {
			perror("send");
		}
	}

	client_threads[thread_number].is_free = 1;
	pthread_exit(NULL);
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

	unlink(local.sun_path);
	bind_result = bind(socket_id, (struct sockaddr*)&local, sizeof(local));
	if (bind_result == -1) {
		perror("bind");
	}

	listen_result = listen(socket_id, 0);
	if (bind_result == -1) {
		perror("listen");
	}

	int i;
	for (i = 0; i < MAX_CLIENTS; i++) {
		client_threads[i].is_free = 1;
	} 
	
	client_thread_args args;
	while (1) {
		nid=accept(socket_id, (struct sockaddr*)&local, &sockaddr_un_size);
		if (nid == -1) {
			perror("nid");
		}

		for (i = 0; i < MAX_CLIENTS; i++) {
			if (client_threads[i].is_free) {
				client_threads[i].is_free = 0;
				args.nid = &nid;
				args.thread_number = i;
				pthread_create(&client_threads[i].thread, NULL, client_routine, (void*)&args); 
				break;
			}
		} 
		
		close(nid);	
	}

	return EXIT_SUCCESS;
}