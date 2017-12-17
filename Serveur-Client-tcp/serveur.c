#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/un.h>
#include <sys/socket.h>

/* Cette fonction lance la routine d'un fils du serveur qui s'occupe d'un client .
   Elle prend en argument l'id de son socket ainsi que la structure de l'addresse
   C'est ici qu'il faut appliqué le protocole de comunication */

void srvtcpson(int nid,struct sockaddr_in* serv)
{
	/*
	################################################
	           A CODER ( send, recv... )

	           exemple :
	           	envoi de int x = 10
	           	send(nid,&x,sizeof(int),0);
	################################################

	*/ 

	exit(0); /* Fin du fils qui s'occupe du client, le exit evite la bombe fork */
}	



/* Cette fonction lance la routine d'un serveur tcp sur le port en chaine de caractères donné en argument */

void runsrvtcp(char* port)
{

	int sfd; /* Id du socket du père */
	int nid; /* Id du socket d'un fils */
	struct sockaddr_in serv; /* Structure représantant l'addresse */
	int pid; /* Pid du fils, nécessaire por le traitement des processus */
	int addrlen; /* Taille de la structure représantant l'addresse */
	int yes = 1; /* Variable utile pour le setsockopt, c'est un boolean a true */

	addrlen = sizeof(serv); /* On place la taille de la structure dans addrlen, nécessaire pour certaine fonction plus tard */

	sfd = socket(AF_INET,SOCK_DGRAM,0); /* Création du socket */
	if ( sfd == -1 ) /* Traintement de l'erreur potentielle de socket */
	{
		perror("serveur.c : Erreur lors de la creation du socket ");
		exit(-1);
	}


	memset(&serv,'\0',sizeof(struct sockaddr_in)); /* On met toute la structure à zero pour eviter les erreurs */

	serv.sin_family = AF_INET; /* Précise le type d'addresse à utiliser, ici ipv4 */

	serv.sin_port = htons((unsigned short) strtol(port,NULL,0)); /* On précise à la structure son port. S'occupe aussi des conversions nécessaire */

	serv.sin_addr.s_addr = INADDR_ANY; /* précise l'addresse à la structure */

	if( setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1 ) /* Permet l'accès à plusieurs clients. S'occupe aussi des conversions nécessaires */
	{
         perror("serveur.c : erreur lors du setsockopt");
         exit(1);
      }

	if( bind(sfd,(struct sockaddr *)&serv,sizeof(serv)) != 0) /* Association du socket avec son addresse et son port. Traite aussi l'erreur potentielle de bind */
	{
         perror("serveur.c : erreur lors du bind ");
         exit(-1);
    }

    if( listen(sfd,10) != 0 ) /* Le serveur va lancer l'"écoute" sur le socket préalablement créé. Traite aussi l'erreur potentielle de listen */
    {
         perror("serveur.c : erreur lors du listen ");
         exit(-1);
    }

    while ( 1 )
    {

    	nid = accept(sfd,(struct sockaddr *)&serv,&addrlen); /* Accepte la connection d'un client */

    	if(nid == -1) /* Traitement de l'erreur potentielle du accept */
    	{
            perror("serveur.c : erreur lors du accept ");
            exit(-1);
        }

        pid = fork(); /* Ce fork permet d'accepter les clients en leur proposant un socket dans un processus "dedié" */

        if ( pid == -1) /* Traitement de l'erreur potentielle du fork */
        {
        	perror("serveur.c Erreur lors du fork ");
        	exit(-1);
        }

        if ( pid == 0 ) /* Si c'est le fils alors */
        {
        	srvtcpson(nid,&serv); /* On lance la routine du fils, le protocole */ 
        }

        if ( pid > 0 ) /* Si c'est le père alors */
        {
        	close(nid); /* On ferme le socket dédié vu qu'un fils s'en occupe. */
        }
    }
}



/*  Fonction main, lance le programme 
	argc doit être égal à deux ici, a.out <port>
*/

void main(int argc,char** argv)
{
	if ( argc != 2 )
	{
		printf("Vous vous etes trompez dans les arguments. \n Usage : %s <port>",argv[0]);
		exit(-1);
	}
	runsrvtcp(argv[1]); /* Lance le serveur */
}