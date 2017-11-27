#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#define SRV_SOCK_PATH "/tmp/srv"
#define MESSAGE "coucou"


void main(int argc,char** argv)
{
	int sfd,nbyte;

	int connexion;

	struct sockaddr_un local,serv;

	sfd = socket(AF_UNIX,SOCK_STREAM,0);

	char* chaine = malloc(sizeof(char)*6);

	memset(&serv, '\0' , sizeof( struct sockaddr_un ) );

	serv.sun_family = AF_UNIX;

	strncpy(serv.sun_path, SRV_SOCK_PATH , sizeof(local.sun_path) - 1);

	connexion = connect(sfd,(struct sockaddr *) &serv, sizeof(struct sockaddr_un) );

	if ( connexion == -1)
	{
		perror("Erreur lors de connect du client ");
		exit(-1);
	}

	while ( 1 )
	{
		chaine = "coucou";
		nbyte = send(sfd,chaine,6,0);
		if ( nbyte < 1 )
		{
			perror("Erreur lors de l'envoi client ");
			exit(-1);
		}
		printf("Client envoi : %s\n",chaine);
		nbyte = recv(sfd,chaine,6,0);
		if ( nbyte == 0)
		{
			printf("Le serveur est mort\n");
			exit(-1);
		}
		if ( nbyte < 0 )
		{
			perror("Erreur lors de la reception client");
			exit(-1);
		}
		printf("Client recoit : %s\n",chaine);
		sleep(4);
	}


}