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
	int error;
	int verificateur1,verificateur2,verificateur3;
	verificateur1 = 10;

	verificateur2 = open("foo.dat",O_CREAT|O_TRUNC|O_WRONLY,0644);

	if ( verificateur2 == -1 )
	{
		perror("Erreur lors de l'ouverture de foo.dat n1.");
		exit(-11);
	}

	for ( i=0 ; i<10 ; i++)
	{
		error = write(verificateur2,&i,1);

		printf("debug -> %c \n",i+'0');

		if ( error < 0)
		{
			perror("Erreur lors de l'ecriture de foo.dat");
			close(verificateur2);
			exit(-12);
		}

	}

	close(verificateur2); 

	pid01 = fork();

	if ( pid01 == -1)rror("erreur lors de l'ouverture de foo.dat n2.");
			exit(-13);
		{
			perror("Erreur lors du fork n1");
			exit(-1);
		}

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

		verificateur3 = open("foo.dat",O_RDONLY,0444);
		if ( verificateur3 == -1 )
		{
			perror("erreur lors de l'ouverture de foo.dat n2.");
			exit(-13);
		}
		for ( i=0 ; i<5 ; i++)
		{
			error = read(verificateur3,&buffver1,1);

			printf("debug2 -> %c \n",i+'0');

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
		for ( i=5 ; i< 10 ; i++ )
		{

			error = read(verificateur3,&buffver1,1);

			printf("debug3 -> %c \n",i='0');

			if ( error < 0 )
			{
				perror("Erreur lors de la lecture n2 de foo.dat.\n Descripteur fichier probablement non herite par le fils.");
				close(verificateur3);
				exit(-15);
			}

			printf("(Fils) : %c \n",buffver1+'0');
			printf("Fin du processus fils n2\n");
			exit(0);

		}
	}
}