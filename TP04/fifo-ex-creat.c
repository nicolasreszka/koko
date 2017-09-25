#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(int argc,char** argv)
{
	char commande[80];
	if (argc != 2)
	{
		printf("Mauvais arguments.\n utilisation : %s <nom fichier fifo a creer>\n",argv[0]);
		exit(-1);
	}
	sprintf(commande,"mkfifo -m 0644 %s",argv[1]);
	system(commande);
}