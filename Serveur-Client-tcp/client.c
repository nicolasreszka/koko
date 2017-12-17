#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/time.h>


void routinecltclient(int sfd,struct sockaddr_in* serv)
{
	/*
	################################################
	           A CODER ( send, recv... )

	           exemple :
	           	envoi de int x = 10
	           	send(nid,&x,sizeof(int),0);
	################################################

	*/ 
}


void runclttcp(char* addresse,char* port)
{

	int sfd; /* Id du socket */
	struct sockaddr_in serv; /* Structure représentant l'addresse */
	int addrlen; /* Taille de la structure représantant l'addresse */

	addrlen = sizeof(serv);  /* On place la taille de la structure dans addrlen, nécessaire pour certaine fonction plus tard */

	sfd = socket(AF_INET,SOCK_DGRAM,0); /* Création du socket */
	if ( sfd == -1 ) /* Traintement de l'erreur potentielle de socket */
	{
		perror("client.c : Erreur lors de la creation du socket");
		exit(-1);
	}

	memset(&serv,'\0',sizeof(struct sockaddr_in)); /* On met toute la structure à zero pour eviter les erreurs */

	serv.sin_family = AF_INET; /* Définis le type d'addresse à utiliser. */

	serv.sin_port = htons((unsigned short) strtol(port,NULL,0)); /* Place le port dans la structure */

	s = inet_pton(AF_INET,addresse,&serv.sin_addr); /* Conversion de l'addresse de la forme humain à la forme machine, puis place celle-ci dans la structure */

	if ( s <= 0 ) /* Traitement des erreurs de conversion possible */
    {
    	if ( s == 0 )
    	{
    		printf("client.c : L'addresse donnee n'est pas bien presente\n");
    		exit(-1);
    	}
    	if ( s < 0 )
    	{
    		perror("client.c : Erreur lors de inet_pton ");
    		exit(-1);
    	}
    }

    if( connect(sfd,(struct sockaddr*) &serv,addrlen) == -1 ) /* Connexion au serveur. Traite aussi les erreurs de connect possible.*/
    {
         perror("client.c : Erreur lors du connect ");
         close(sfd);
         exit(1);
    }

    routinecltclient(sfd,&serv); /* Lance la routine du client (protocole) */
}

void main(int argc,char** argv)
{
	if ( argc != 3)
	{
		printf("Vous vous etes trompez dans les arguments. \n Usage : %s <addresse> <port>",argv[0]);
		exit(-1);
	}

	runclttcp(argv[1],argv[2]);

}