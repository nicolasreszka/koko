#ifndef H_GL_SERVEUR
#define H_GL_SERVEUR

void runsrvtcp(char* port,void (*pf)(int, struct sockaddr_in*)); /* ATTENTION, la fonction donnée en paramêtre doit NECESSAIREMENT être terminée avec un exit */

#endif