#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

union seman
{
	int val;
	struct semid_ds *buf;
	unsigned short int * array;
	struct seminfo * _buf;
};


void main(void)
{
	int key,semid,err;
	union seman s;
	s.val = 1;
	key = ftok("/tmp",'a');
	if ( key < 0 )
	{
		perror("Erreur lors de ftok ");
		exit(-1);
	}
	semid = semget(key,3,0666|IPC_CREAT|IPC_EXCL);
	if ( semid < 0 )
	{
		perror("Erreur lors de semget ");
		exit(-1);
	}
	err = semctl(semid,0,SETVAL,s);
	if ( err < 0 )
	{
		perror("Erreur lors de semctl ");
		exit(-1);
	}
	s.val=0; /* ici */
	err = semctl(semid,1,SETVAL,s);
	if ( err < 0 )
	{
		perror("Erreur lors de semctl ");
		exit(-1);
	}
	err = semctl(semid,2,SETVAL,s);
	if ( err < 0 )
	{
		perror("Erreur lors de semctl ");
		exit(-1);
	}
}