#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define LOGLEN 16

struct log2data
{
	char log[LOGLEN]; // LOGLEN = 16 ?
	char file[LOGLEN];
};

struct log2data* getDataLogin(char* nomFichier,unsigned int tailletableau)
{
	int fd,i=0,err;
	struct log2data* tableau;
	struct stat fi;
	fd = open(nomFichier,O_RDONLY,0444);
	if (fd<0)
	{
		perror("Search : Erreur lors du open ");
		exit(-1);
	}
	fstat(fd,&fi);
	tableau = malloc(tailletableau*sizeof(struct log2data));
	while (1)
	{
		err = read(fd,&tableau[i],sizeof(struct log2data));
		if ( err < 0 )
		{
			perror("Search : Erreur lors du read (l31) ");
			exit(-1);
		}

		if ( err == 0)
		{
			close(fd);
			return tableau;
		}
		i++;
	}
} 

char* search(struct log2data* st,char* login,unsigned int tailletableau)
{
	int i = 0;
	while( i < tailletableau )
	{
		if ( strcmp(st[i].log,login) == 0 )
		{
			return st[i].file;
		}
		i++;
	}

	return NULL;
}
