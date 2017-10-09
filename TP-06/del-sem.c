#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

void main(void)
{
	int key,semid,err;
	key = ftok("/tmp",'a');
	if ( key < 0 )
	{
		perror("Erreur lors de ftok ");
		exit(-1);
	}
	semid = semget(key,3,0);
	if ( semid < 0 )
	{
		perror("Erreur lors de semget ");
		exit(-1);
	}
	err = semctl(semid,0,IPC_RMID);
	if ( err < 0 )
	{
		perror("Erreur lors de semctl ");
		exit(-1);
	}
}