#ifndef H_GL_CLIENT
#define H_GL_CLIENT

void runclttcp(char* addresse,char* port,void (*routinecltclient)(int, struct sockaddr_in*));

#endif