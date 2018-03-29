#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "cryptmath.h"
#include "serveur.h"
#include "client.h"


void dh_client_routine(int sfd,struct sockaddr_in* serv)
{
	/*
	################################################
	           A CODER ( send, recv... )

	           exemple :
	           	envoi de int x = 10
	           	send(nid,&x,sizeof(int),0);
	################################################

	*/ 
	exit(0);
}

void dh_serv_routine(int nid,struct sockaddr_in* serv)
{
	/*
	################################################
	           A CODER ( send, recv... )
	           exemple :
	           	envoi de int x = 10
	           	send(nid,&x,sizeof(int),0);
	################################################
	*/ 

	exit(0); /* Fin du fils qui s'occupe du client, le exit evite la bombe fork */
}

void dh_serveur(char* port)
{
	runsrvtcp(port,&dh_serv_routine);
}

void dh_client(char* addresse,char* port)
{
	runclttcp(addresse,port,&dh_client_routine);
}