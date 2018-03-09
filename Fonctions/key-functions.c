unsigned char get_char_key_from_file(char * file_name)
{
  int fd;
  int err;
  unsigned char result;
  fd = open(file_name,O_RDONLY,0444);
  if ( fd == -1 )
  {
    perror("get_char_key_from_file : Erreur lors du open ");
    exit(-1);
  }
  err = read(fd,&result,sizeof(char));
  if ( err < (int) sizeof(char) )
  {
    perror("get_char_key_from_file : Erreur lors du read ");
    exit(-1);
  }
  err = close(fd);
  if ( err == -1)
  {
    perror("get_char_key_from_file : Erreur lors du close ");
    exit(-1);
  }
  return result;
}

unsigned short get_short_key_from_file(char * file_name)
{
  int fd;
  int err;
  unsigned short result;
  fd = open(file_name,O_RDONLY,0444);
  if ( fd == -1 )
  {
    perror("get_short_key_from_file : Erreur lors du open ");
    exit(-1);
  }
  err = read(fd,&result,sizeof(short));
  if ( err < (int) sizeof(short))
  {
    perror("get_short_key_from_file : Erreur lors du read ");
    exit(-1);
  }
  err = close(fd);
  if ( err == -1)
  {
    perror("get_short_key_from_file : Erreur lors du close ");
    exit(-1);
  }
  return result;
}

unsigned int get_int_key_from_file(char * file_name)
{
  int fd;
  int err;
  unsigned int result;
  fd = open(file_name,O_RDONLY,0444);
  if ( fd == -1 )
  {
    perror("get_int_key_from_file : Erreur lors du open ");
    exit(-1);
  }
  err = read(fd,&result,sizeof(int));
  if ( err < (int) sizeof(int))
  {
    perror("get_int_key_from_file : Erreur lors du read ");
    exit(-1);
  }
  err = close(fd);
  if ( err == -1)
  {
    perror("get_int_key_from_file : Erreur lors du close ");
    exit(-1);
  }
  return result;
}

unsigned long get_long_key_from_file(char * file_name)
{
  int fd;
  int err;
  unsigned long result;
  fd = open(file_name,O_RDONLY,0444);
  if ( fd == -1 )
  {
    perror("get_long_key_from_file : Erreur lors du open ");
    exit(-1);
  }
  err = read(fd,&result,sizeof(long));
  if ( err < (int) sizeof(long))
  {
    perror("get_long_key_from_file : Erreur lors du read ");
    exit(-1);
  }
  err = close(fd);
  if ( err == -1)
  {
    perror("get_long_key_from_file : Erreur lors du close ");
    exit(-1);
  }
  return result;
}

unsigned long long get_long_long_key_from_file(char * file_name)
{
  int fd;
  int err;
  unsigned long long result;
  fd = open(file_name,O_RDONLY,0444);
  if ( fd == -1 )
  {
    perror("get_long_long_key_from_file : Erreur lors du open ");
    exit(-1);
  }
  err = read(fd,&result,sizeof(long long));
  if ( err < (int) sizeof(long long))
  {
    perror("get_long_long_key_from_file : Erreur lors du read ");
    exit(-1);
  }
  err = close(fd);
  if ( err == -1)
  {
    perror("get_long_long_key_from_file : Erreur lors du close ");
    exit(-1);
  }
  return result;
}

void * get_unkown_key_from_file(char * file_name)
{
  int fd;
  int err;
  void * result;
  fd = open(file_name,O_RDONLY,0444);
  if ( fd == -1 )
  {
    perror("get_unkown_key_from_file : Erreur lors du open ");
    exit(-1);
  }
}