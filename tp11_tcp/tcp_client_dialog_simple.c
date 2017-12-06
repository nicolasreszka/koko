#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include "sys/socket.h"
#include "arpa/inet.h"

#define MESSAGE_SIZE 109

int		main(int argc, char** argv)
{
	if (argc != 3) 
	{
		printf("Usage: %s <addresse v4> <port>\n", argv[0]);
	}

	struct sockaddr_in	tcp_socket_address;
	socklen_t 			sockaddr_in_size = sizeof(struct sockaddr_in);
	int 				tcp_socket_descriptor, read_result, send_result, recv_result;
	int 				yes = 1;
	char				message[MESSAGE_SIZE];
	char				response[MESSAGE_SIZE];

	tcp_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (tcp_socket_descriptor == -1) 
	{
		perror("socket");
		exit(errno);
	}

	setsockopt(tcp_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	memset(&tcp_socket_address, 0, sockaddr_in_size);
	tcp_socket_address.sin_family = AF_INET;
	tcp_socket_address.sin_port = htons((short)strtol(argv[2],NULL,0));
	tcp_socket_address.sin_addr.s_addr = inet_addr(argv[1]);;

	if (connect(tcp_socket_descriptor, (struct sockaddr*)&tcp_socket_address, sockaddr_in_size) != 0)
	{
		perror("connect");
		exit(errno);
	}

	while (1)
	{
		memset(message, '\0', MESSAGE_SIZE);
		memset(response, '\0', MESSAGE_SIZE);
		read_result = read(0,message,MESSAGE_SIZE);

		if (read_result == -1) 
		{
			perror("read");
			exit(errno);
		} 
		else 
		{
			if (strncmp(message,"quit",4) == 0) 
			{
				close(tcp_socket_descriptor);
				break;
			}
			else 
			{
				send_result = send(tcp_socket_descriptor,message,MESSAGE_SIZE,0);

				if (send_result == -1)
				{
					perror("send");
					exit(errno);
				}
				else 
				{
					recv_result = recv(tcp_socket_descriptor,response,MESSAGE_SIZE,MSG_WAITALL);
					if (recv_result == -1)
					{
						perror("recv");
						exit(errno);
					}	
					else
					{
						printf("server response: %s\n", response);
					}
				}
			}
		}
	}

	exit(EXIT_SUCCESS);
}