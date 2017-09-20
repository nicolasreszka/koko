#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(void)
{
	char i,buffver1;
	int pid01,pid02; /* Ids des processus fils 1 et 2 */
	int error; /* variable qui detecte les erreurs lors de open write et read */
	int verificateur1,verificateur2,verificateur3;
	verificateur1 = 10; /* variable test */

	/*
	##############################################################################
	#			Creation et initialisation d'un fichier à lire                   #
	#                  en écrivant 0123456789 dedans                             #
	##############################################################################
	*/

	verificateur2 = open("foo.dat",O_CREAT|O_TRUNC|O_WRONLY,0644);

	if ( verificateur2 == -1 )
	{
		perror("Erreur lors de l'ouverture de foo.dat n1.");
		exit(-11);
	}

	for ( i=0 ; i<10 ; i++)
	{
		error = write(verificateur2,&i,1);

		if ( error < 0)
		{
			perror("Erreur lors de l'ecriture de foo.dat");
			close(verificateur2);
			exit(-12);
		}

	}

	close(verificateur2); 

	/*
	###############################################################################
	#				          Fin initialisation								  #
	###############################################################################
	*/


	/*
	###############################################################################
	#                                Premier fork                                 #
	#            But : Déterminer si les variables sonr hérité par le fils.       #
	###############################################################################
	*/

	pid01 = fork();

	/* ### Gestion de l'erreur possible du fork. ### */

	if ( pid01 == -1)
		{
			perror("Erreur lors du fork n1");
			exit(-1);
		}


	/*
	################################################################################
	#                         Code éxécuté par le fils.                            #
	################################################################################
	*/

	else if ( pid01 == 0 )
		{

			if ( verificateur1 == 10)
			{
				printf("Le fils herite des variables du pere et de leurs valeurs.\n");
			}

			else
			{
				printf("Le fils herite des variables du pere mais pas de leurs valeurs.\n");
			}
			printf("Processus fils 1 termine.\n");
			exit(0);
		}

	/*
	################################################################################
	#                      Fin code éxécuté par le fils.                           #
	################################################################################
	*/


	/*
	################################################################################
	#              Le pere va lire les 5 premiers numéro du fichier.               #
	#                          Et le fils les 5 suivants                           #
	# réponses attendues :                                                         #
	#  (pere): 0                                                                   #
	#  (pere): 1                                                                   #
	#  (pere): 2                                                                   #
	#  (pere): 3                                                                   #
	#  (pere): 4                                                                   #
	#  (fils): 5                                                                   #
	#  (fils): 6                                                                   #
	#  (fils): 7                                                                   #
	#  (fils): 8                                                                   #
	#  (fils): 9                                                                   #
	################################################################################
	*/

	verificateur3 = open("foo.dat",O_RDONLY,0444);

	if ( verificateur3 == -1 )
	{
		perror("erreur lors de l'ouverture de foo.dat n2.");
		exit(-13);
	}
	for ( i=0 ; i<5 ; i++)
	{
		error = read(verificateur3,&buffver1,1);

		if ( error < 0 )
		{
			perror("Erreur lors de la lecture n1 de foo.dat.");
			close(verificateur3);
			exit(-14);
		}

		printf("(Pere) : %c \n",buffver1+'0');
	}


	pid02 = fork();

	if ( pid02 == -1 )
	{
		perror("Erreur lors du fork n2");
		exit(-2);
	}

	else if ( pid02 == 0 )
	{
		for ( i=5 ; i < 10 ; i++ )
		{

			error = read(verificateur3,&buffver1,1);

			if ( error < 0 )
			{
				perror("Erreur lors de la lecture n2 de foo.dat.\n Descripteur fichier probablement non herite par le fils.");
				close(verificateur3);
				exit(-15);
			}

			printf("(Fils) : %c \n",buffver1+'0');

		}

		if ( buffver1+'0' == '9' )
		{
			printf("Un fils herite des fd du père et des positions de ces fichiers. \n");
		}
		else
		{
			printf("Un fils n'herite pas des fd du père et des positions de ces fichiers. \n");
		}

		printf("Fin du processus fils n2\n");
		exit(0);
	}
}