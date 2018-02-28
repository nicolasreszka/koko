#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/sem.h"

int 	main(void) 
{

	key_t	key_1, key_2, key_3;
	int		semid_1, semid_2, semid_3; 

	key_1 = ftok("/tmp",'1');
	key_2 = ftok("/tmp",'2');
	key_3 = ftok("/tmp",'3');

	if (key_1 == -1 || key_2 == -1 || key_3 == -1)
	{
		perror("ftok");
		exit(errno);
	}

	semid_1 = semget(key_1, 1, 0);
	semid_2 = semget(key_2, 1, 0);
	semid_3 = semget(key_3, 1, 0);

	if (semid_1 == -1 || semid_2 == -1 || semid_3 == -1)
	{
		perror("semget");
		exit(errno);
	}

	semctl(semid_1, 0, IPC_RMID);
	semctl(semid_2, 0, IPC_RMID);
	semctl(semid_3, 0, IPC_RMID);

	exit(EXIT_SUCCESS);
}
