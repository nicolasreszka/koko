#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

struct param{
  unsigned short key;
  unsigned char distance;
  char sens;
  int fd_destination;
  int fd_fileToRead;
  int fileToRead_size;
  unsigned char key_array[2];
};
typedef struct param parametres;

int nb_threads = 0;

pid_t gettid(void){
  return syscall(__NR_gettid);
}

int getSizeOfFile(int fd){
  int fileToRead_size = -1;
  int x = -1;
  int z;
  while(x != 0){
    x = read(fd, &z, 1);
    fileToRead_size++;
  }
  return fileToRead_size;
}


unsigned char rotl(unsigned char* octet, int distance){
  unsigned char lost_bit;
  unsigned char tmp_byte;

  for(int i = 0; i < distance; i++){
    tmp_byte = *octet;
    lost_bit = (tmp_byte >> 7);
    *octet = (*octet << 1);
    *octet = (*octet | lost_bit);
  }

  return *octet;
}

unsigned char rotr(unsigned char* octet, int distance){
  unsigned char lost_bit;
  unsigned char tmp_byte;

  for(int i = 0; i < distance; i++){
    tmp_byte = *octet;
    lost_bit = (tmp_byte << 7);
    *octet = (*octet >> 1);
    *octet = (*octet | lost_bit);
  }
  return *octet;
}

unsigned char* do_perm(parametres* param, unsigned char* buff, int actual_byte){
  unsigned short key = param->key;
  char decallage;
  decallage = actual_byte%16;
  unsigned char mask = 0x1;
  key = key & (mask << decallage);
  key = key >> decallage;
  //Rotation
  if(param->sens == -1){
    *buff = rotr(buff, param->distance);
  } else {
    *buff = rotl(buff, param->distance);
  }
  //On XOR avec la clé
  if(key == 1){
    *buff = *buff ^ param->key_array[1];
  } else {
    *buff = *buff ^ param->key_array[0];
  }
  return buff;
}

void* start_routine(void* arg){
  parametres* param = (parametres*) arg;
  int num_thread = (gettid() - getpid())%nb_threads;
  printf("THREAD créé, num = %d,PID = %d, TID = %d\n", num_thread, getpid(), gettid());

  int actual_byte = param->fileToRead_size/nb_threads * num_thread;
  int size_to_read = param->fileToRead_size/nb_threads;
  printf("Thread n°%d Octet de départ = %d Nombre d'octets à analyser = %d\n",num_thread, actual_byte, size_to_read );
  unsigned char buff;
  int y = -1;
  int i = 0;
  while( y != 0 && (size_to_read != 0)){
    y = pread(param->fd_fileToRead, &buff, 1, actual_byte);
    unsigned char* byte = do_perm(param, &buff, actual_byte);
    pwrite(param->fd_destination, byte, 1, actual_byte);
    actual_byte++;
    size_to_read--;
  }
  return NULL;}

int main(int argc, char ** argv) {

  parametres param = {0,0,0,0,0,0,{0,0}};


  if(argc != 4) {
    fprintf(stderr, "Utilisation : %s <N threads> <Fichier a permuter> <Fichier parametres>", argv[0]);
    exit(1);
  }
  nb_threads = atoi(argv[1]);
  if(nb_threads < 1){
    perror("nb_thread should be >= 1\n");
    exit(2);
  }
  int fd_param = open(argv[3], O_RDONLY);
  if(fd_param == -1){
    perror("Couldn't open Param file\n");
    exit(3);
  }

  int y = read(fd_param, &param.key, sizeof(unsigned short));
  if(y == 0){
    perror("Couldn't read key\n");
    exit(3);
  }
  y = read(fd_param, &param.distance, sizeof(unsigned char));
  if(y == 0){
    perror("Couldn't read distance\n");
    exit(3);
  }
  y = read(fd_param, &param.sens, sizeof(char));
  if(y == 0){
    perror("Couldn't read sens\n");
    exit(3);
  }
  int fd_destination = open("bar", O_CREAT|O_TRUNC|O_WRONLY, 0666);
  if(fd_destination == -1){
    perror("Couldn't create destination file\n");
    exit(4);
  }
  int fd_fileToRead = open(argv[2], O_RDONLY);
  if(fd_fileToRead == -1){
    perror("Couldn't read file to encrypt\n");
    exit(5);
  }

  param.fd_fileToRead = fd_fileToRead;
  param.fd_destination = fd_destination;
  param.fileToRead_size = getSizeOfFile(fd_fileToRead);

  unsigned short key_tmp = param.key;
  param.key_array[0] = (char)(key_tmp & 0xff);
  param.key_array[1] = (char)((key_tmp >> 8) & 0xff);
  int offset = 0;
  pthread_t th[nb_threads];

  for(int i = 0; i < nb_threads; i++){
    pthread_create(&th[i], NULL, start_routine, &param);
  }
  for(int i = 0; i < nb_threads; i++){
    pthread_join(th[i], NULL);
  }

  return 0;
}
