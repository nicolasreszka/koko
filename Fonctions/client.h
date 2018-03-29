#ifndef H_GL_SERVEUR
#define H_GL_SERVEUR

void routinecltclient(int sfd,struct sockaddr_in* serv);
void runclttcp(char* addresse,char* port);

#endif