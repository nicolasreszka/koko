#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "pthread.h"
#include "sys/syscall.h"

#define MAX_CLIENTS 20
#define MESSAGE_SIZE 109

void* 	client_routine(void *arg)
{
	int 	nid, send_result, recv_result;
	char	message[MESSAGE_SIZE];

	nid = *(int*) arg;

	while (1) {
		memset(message, '\0', MESSAGE_SIZE);
		recv_result = recv(nid,message,MESSAGE_SIZE,MSG_WAITALL);

		if (recv_result == -1) 
		{
			perror("recv");
			pthread_exit(NULL);
		} 
		else if (recv_result == 0)
		{
			printf("client has left\n");
			break;
		}
		else
		{
			printf("%s\n",message);
			send_result = send(nid,message,MESSAGE_SIZE,MSG_EOR);
			if (send_result == -1) 
			{
				perror("send");
				pthread_exit(NULL);
			}
		}
	}
	close(nid);
	pthread_exit(NULL);
}


int 	main(int argc, char** argv) {
	if (argc != 2) 
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in	tcp_socket_address;
	socklen_t 			sockaddr_in_size = sizeof(struct sockaddr_in);
	int 				tcp_socket_descriptor, nid;
	int 				bind_result, listen_result;
	int 				yes = 1;
	pthread_t 			client_thread;
	
	tcp_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (tcp_socket_descriptor == -1) 
	{
		perror("socket");
		exit(errno);
	}

	setsockopt(tcp_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	memset(&tcp_socket_address, 0, sockaddr_in_size);
	tcp_socket_address.sin_family = AF_INET;
	tcp_socket_address.sin_port = htons((short)strtol(argv[1],NULL,0));
	tcp_socket_address.sin_addr.s_addr = INADDR_ANY;

	bind_result = bind(tcp_socket_descriptor, (struct sockaddr*)&tcp_socket_address,sockaddr_in_size);

	if (bind_result == -1)
	{
		perror("bind");
		exit(errno);
	}

	listen_result = listen(tcp_socket_descriptor, MAX_CLIENTS);

	if (listen_result == -1)
	{
		perror("listen");
		exit(errno);
	}

	while (1) 
	{
		nid = accept(tcp_socket_descriptor, (struct sockaddr*)&tcp_socket_address, &sockaddr_in_size);

		if (nid == -1) 
		{
			perror("accept");
			exit(errno);
		}

		pthread_create(&client_thread,NULL,client_routine, (void*)&nid);
	}

	return EXIT_SUCCESS;
}