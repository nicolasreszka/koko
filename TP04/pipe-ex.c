#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(void)
{
	int pidPf1,pidPf2,pidPf1f1,rest,rese,err;
	int pp[2];
	err = pipe(pp);
	if ( err == -1 )
	{
		perror("Erreur lors de la creation du pipe ");
		exit(-100);
	}
	pidPf1 = fork();

	if ( pidPf1 == -1)
	{
		perror("Erreur lors du fork Pf1 ");
		exit(-1);
	}

	/*
	##################################################
	#                    code Pf1                    #
	##################################################
	*/

	if( pidPf1 == 0)
	{
		pidPf1f1 = fork();

		if ( pidPf1f1 == -1)
		{
			perror("Erreur lors du fork Pf1f1 ");
			exit(-11);
		}

		/*
		##################################################
		#                  code Pf1f1                    #
		##################################################
		*/

		if( pidPf1f1 == 0)
		{
			close(pp[1]);
			while(1)
			{
				read(pp[0],&rest,4);
				printf("ici Pf1f1 : %d je lis %d dans le tube\n",getpid(),rest);
				sleep(1);
			}
		}
		close(pp[0]);
		close(pp[1]);

	}

	/*
	##################################################
	#                    code P                    #
	##################################################
	*/

	if ( pidPf1 > 0)
	{
		pidPf2 = fork();
		if( pidPf2 == -1)
		{
			perror("Erreur lors du fork Pf2 ");
			exit(-2);
		}

		/*
		##################################################
		#                    code Pf2                    #
		##################################################
		*/
		if ( pidPf2 == 0)
		{
			close(pp[0]);
			rese = getpid();
			while(1)
			{
				rese++;			
				write(pp[1],&rese,4);
				printf("Ici pf2: %d, J'écris %d dans le tube.\n",getpid(),rese);
				sleep(3);
			}
		}
		if(pidPf2 > 0)
		{
			close(pp[0]);
			close(pp[1]);
			printf("Ici P.\n");
			sleep(2);
		}
	}
}