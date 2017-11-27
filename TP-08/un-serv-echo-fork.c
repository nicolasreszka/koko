#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#define MY_SOCK_PATH "/tmp/srv"
#define MESSAGE "coucou"

void main(int argc,char** argv)
{

	int sfd; /* ID du socket de base */
	int nid; /* ID du socket dupliqué par le fork */
	int x; /* Variable de la gestion du fork */
	int err; /* Variable de gestion des erreurs */
	int nbyte; /* Nombre d'octet lut ou écrits */
	int addrlen; /* Taille de la structure */
	struct sockaddr_un local; /* Structure de l'addresse du serveur (locale) */
	char* chaine = malloc(sizeof(char)*6); /* Buffer de reception et d'envoi */
	int yes = 1; /* Valeur a donner en argument a setsockopt */

	/* Création du socket */
	sfd = socket(AF_UNIX,SOCK_STREAM,0);
	if ( sfd == -1 )
	{
		perror("Erreur lors de la creation du socket client ");
		exit(-1);
	}

	err = setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
	if ( err == -1)
	{
		perror("Erreur lors de setsocketopt serveur");
		exit(-1);
	}

	/* On met la structure à zero partout. */
	memset(&local, '\0' , sizeof( struct sockaddr_un ) );

	/* On dit que l'addresse sera de type locale */
	local.sun_family = AF_UNIX;

	/* On place l'addresse locale dans la structure 
		local.sun_path variable qui contient l'addresse 
		MY_SOCK_PATH = adresse*/
	strncpy(local.sun_path, MY_SOCK_PATH , sizeof(local.sun_path) - 1);

	/* On place la taille de la structure dans une variable c'est bécessaire pour plus tard. */
	addrlen = sizeof(local);

	/* On supprime le fichier du reseau local si il existe déja. */
	unlink(MY_SOCK_PATH);


	/* On associe le socket avec le fichier local */
	if ( bind(sfd,(struct sockaddr *) &local, sizeof(struct sockaddr_un)) != 0)
	{
		perror("Erreur lors du bind serveur ");
		exit(-1);
	}


	/* ****************** */
	err = listen(sfd,5);


	/* La routine */
	while (1)
	{

		/* Si il y a une nouvelle connexion, on creer un socket identique */
		nid = accept(sfd,(struct sockaddr *)&local,&addrlen);
		if ( nid == -1)
		{
			perror("Erreur lors du accept du serveur ");
			exit(-1);
		}

		/* On fork pour pouvoir gerer une connexion supplementaire */
		x = fork();
		if ( x == -1 )
		{
			perror("Erreur lors du fork serveur ");
			exit(-1);
		}

		/* fils : */
		if ( x == 0 )
		{

			/* On ferme le socket du père */
			close(sfd);
			while ( 1 )
			{
				/* On attend que le client envoie quelquechose */
				nbyte = recv(nid,chaine,6,0);
				if ( nbyte == -1)
				{
					perror("Erreur lors de la reception serveur ");
					exit(-1);
				}
				if ( nbyte == 0)
				{
					printf("Serveur (%d) : Le client est parti \n",getpid());
					close(nid);
					exit(0);
				}
				if ( nbyte < 6 )
				{
					printf("Serveur (%d) : Je n'ai pas tous recu !\n",getpid());
					exit(-1);
				}
				printf("Serveur (%d) : recoit : %s\n",getpid(), chaine);

				/* On envoie le meme message au client */
				nbyte = send(nid,chaine,6,0);
				if ( nbyte <= -1)
				{
					perror("Serveur : Erreur lors de l'envoi (send <= -1)");
					exit(-1);
				}
				if ( nbyte == 0)
				{
					printf("Serveur (%d) : Le client n'est plus la.\n",getpid() );
				}
				if ( nbyte < 6)
				{
					printf("Serveur (%d) : Je n'ai pas pu tout envoyer\n",getpid());
					exit(-1);
				}
				printf("Serveur (%d) envoi : %s\n",getpid(), chaine);
			}
		}

		/* pere : */
		if ( x > 0 )
		{
			/* On ferme la copie du socket dans le pere ( inutile ) */
			close(nid);
		}
	}
}

