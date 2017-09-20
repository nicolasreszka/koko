#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int cnt = 2; // passage nécessaire par une variable globale
void * tachecnt1(void* arg)
{
  //int *par = (int*)arg;
  cnt++;
  printf("%d cnt1: addr(cnt)=%p cnt=%d \n",getpid(),arg,cnt);
}

void * tachecnt2(void* arg )
{
  //int *par = (int*)arg;
  cnt--;
  printf("%d cnt2: addr(cnt)=%p cnt=%d \n",getpid(),arg,cnt);
}

void main(void)
{
  int cnt = 2;
  pthread_t th,th2;
  pthread_create(&th,NULL,tachecnt1,&cnt);
  pthread_create(&th2,NULL,tachecnt2,&cnt);
  pthread_join(th,NULL);
  pthread_join(th2,NULL);
  printf("%d(pere) : addr(cnt)=%p cnt=%d \n",getpid(),&cnt,cnt);
}
