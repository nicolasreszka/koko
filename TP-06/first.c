#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/sem.h>

/* arv 1 = temps */
void main(int argc,char** argv)
{
	int i;
	int key,semid,err;
	if (argc != 2)
	{
		printf("Erreur nbr d'arg \n usage : %s <temps a attendre en msec>\n",argv[0]);
		exit(-1);
	}
	const struct timespec s = { 0 , strtol(argv[1],NULL,0)*1000000 };
	struct sembuf st0cl =  {0 , -1 , 0} ;
	struct sembuf st0op =  {1 , 1 , 0} ;
	key = ftok("/tmp",'a');
	if ( key < 0 )
	{
		perror("Erreur lors de ftok ");
		exit(-1);
	}
	semid = semget(key,0,0);
	if ( semid < 0 )
	{
		perror("Erreur lors de semget ");
		exit(-1);
	}
	while ( 1 )
	{
		semop(semid,&st0cl,1);
		if ( err < 0 )
		{
			perror("Erreur lors de l'ouverture semop ");
			exit(-1);
		}
		for ( i = 2 ; argv[0][i] != '\0' ; i++ )
		{
			putchar(argv[0][i]);
			nanosleep(&s,NULL);
			fflush(0);
		}
		putchar(' ');
		fflush(0);
		semop(semid,&st0op,1);
		if ( err < 0 )
		{
			perror("Erreur lors de l'fermeture semop ");
			exit(-1);
		}
	}
}	