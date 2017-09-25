#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void main(int argc,char ** argv)
{
	int fd,buff;
	if ( argc != 2)
	{
		printf("Erreur mauvais arguments.\n Utilisation : %s <nom du fichier fifo>\n",argv[0]);
		exit(-1);
	}
	fd = open(argv[1],O_RDONLY,0444);
	while(1)
	{
		read(fd,&buff,4);
		printf("Ici fifo-ex-rd.c pid : %d Je lis %d dans fifo\n",getpid(),buff);
		sleep(1);
	}
}