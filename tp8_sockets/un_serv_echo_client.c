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
	int read_result, send_result, recv_result;

	socklen_t sockaddr_un_size;
	sockaddr_un_size = sizeof(struct sockaddr_un);

	struct sockaddr_un local;
	memset(&local, 0, sizeof(struct sockaddr_un));
	local.sun_family = AF_UNIX;
	strncpy(local.sun_path, argv[1], 108);

	int socket_id, pid;
	char message[MESSAGE_SIZE];
	

	while(1) {
		memset(message, '\0', MESSAGE_SIZE);

		socket_id=socket(AF_UNIX,SOCK_STREAM,0);
		if (socket_id < 0) {
			perror("socket");
		}

		if (connect(socket_id, (struct sockaddr*)&local, sockaddr_un_size) < 0) {
			perror("connect");
		}

		printf("message ?\n");
		read_result = read(0,message,MESSAGE_SIZE);
		if (read_result == -1) {
			perror("read");
		} else {
			send_result = send(socket_id,message,MESSAGE_SIZE,0);
			if (send_result == -1) {
				perror("send");
			} else {
				recv_result = recv(socket_id,message,MESSAGE_SIZE, MSG_WAITALL);
				if (recv_result == -1) {
					perror("recv");
				} else {
					printf("response : %s\n", message);
				} 
			}
		}		
		close(socket_id);
	}
	
	return EXIT_SUCCESS;
}
