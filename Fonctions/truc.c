#include <dirent.h> 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void get_files(void)
{
  int fd,fd2;
  DIR *d;
  DIR *d2;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      //printf("%s\n", dir->d_name);
      d2 = opendir(".");
      fd = open(dir->d_name,O_RDONLY,0444);
      fd2 = open("buffile",O_WRONLY|O_CREAT|O_TRUNC,0644);
      if (d2)
      {
        while ((dir = readdir(d)) != NULL)
        {
          write(fd2,dir->d_name,sizeof(dir->d_name));
        }
      }
      close(fd);
      close(fd2);
      closedir(d2);
    }
    closedir(d);
  }
}


void main(void)
{
  get_files();
}