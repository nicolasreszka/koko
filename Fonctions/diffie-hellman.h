#ifndef H_GL_DIFFIE
#define H_GL_DIFFIE

void dh_client_routine(int sfd,struct sockaddr_in* serv);
void dh_serv_routine(int nid,struct sockaddr_in* serv);
void srvtcpson(int nid,struct sockaddr_in* serv);
void dh_serveur(char* port);

#endif