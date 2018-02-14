#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotOctetD(unsigned char * octet,int cycle)
{
  unsigned char buff,mask = 0x1;
  int i;
  buff = *octet;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *octet >>= 1;
      buff <<= 7;
      *octet |= buff;
    }
}

void rotOctetG(unsigned char * octet, int cycle)
{
  unsigned char buff,mask = 0x80;
  int i;
  buff = *octet;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *octet <<= 1;
      buff >>= 7;
      *octet |= buff;
    }
}

void rotNibbleD(unsigned char * nibble,int cycle)
{
  unsigned char buff,mask = 0x1;
  int i;
  buff = *nibble;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *nibble >>= 1;
      buff <<= 3;
      *nibble |= buff;
    }
}

void rotNibbleG(unsigned char * nibble,int cycle)
{
  unsigned char buff,mask = 0x8;
  int i;
  buff = *nibble;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *nibble <<= 1;
      buff >>= 3;
      *nibble |= buff;
    }
}

void rotDiade(unsigned char * diade,int cycle)
{
  unsigned char buff;
  int i;
  buff = *diade;
  for ( i = 0 ; i < cycle ; i++ )
    {
      *diade >>= 1;
      buff <<= 1;
      *diade |= buff;
    }
}

void permBitOctet(unsigned char * octet, unsigned int permListe[8])
{
  unsigned char buff=0x0,buff2 = 0x0 ,mask = 0x1;
  int i;
  for ( i = 0 ; i < 8 ; i++)
    {
      buff2 =(*octet & mask);
      buff2 >>= i;
      buff2 <<= permListe[i];
      buff |= buff2;
      mask <<= 1;
    }
  *octet = buff;
}

void permBitNibble(unsigned char * nibble, unsigned int permListe[4])
{
  unsigned char buff=0x0,buff2=0x0,mask=0x1;
  int i;
  for ( i = 0 ; i < 4 ; i++)
    {
      buff2 = (*nibble & mask);
      buff2 >>= i;
      buff2 <<= permListe[i];
      buff |= buff2;
      mask <<= 1;
    }
  *nibble = buff;
}

void permBitDiade(unsigned char * diade, unsigned int permListe[2])
{
  int i;
  unsigned char buff=0x0,buff2=0x0,mask=0x1;
  for ( i = 0 ; i < 2 ; i++ )
    {
      buff2 = (*diade & mask);
      buff2 >>= i;
      buff2 <<= permListe[i];
      buff |= buff2;
      mask <<= 1;
    }
  *diade = buff;
}

void substNibbleOctet(unsigned char * octet, unsigned int substListe[16],int cycle)
{
  int i;
  unsigned char buff=0x0,buff2=0x0, mask = 0xf;
  for ( i = 0 , i < cycle ; i++ )
    {
      buff = *octet;
      buff &= mask;
      mask <<= 4;
      buff = substListe[buff];
      
      buff2 = *octet;
      buff2 &= mask;
      buff2 >>= 4;
      buff2 = substListe[buff];
      buff |= buff2;
      *octet = buff;
    }
}

void substDiadeOctet(unsigned char * octet, unsigned int substListe[4],int cycle)
{
   int i;
   unsigned char buff=0x0,buff2=0x0,buff3=0x0,buff4=0x0, mask = 0x3;
  for ( i = 0 , i < cycle ; i++ )
    {
      buff = *octet;
      buff &= mask;
      mask <<= 2;
      buff = substListe[buff];
      
      buff2 = *octet;
      buff2 &= mask;
      mask <<= 2;
      buff2 >>= 2;
      buff2 = substListe[buff];

      buff3 = *octet;
      buff3 &= mask;
      mask <<= 2;
      buff3 >>= 4;
      buff3 = substListe[buff];
 
      buff4 = *octet;
      buff4 &= mask;
      buff4 >>=6;
      buff4 = substListe[buff];
      
      buff |= buff2;
      buff |= buff3;
      buff |= buff4;
      *octet = buff;
    }
}

void mOctet(unsigned char octet)
{
  int i;
  unsigned char buff[8],mask=0x1;
  for ( i = 0 ; i < 8 ; i++ )
    {
      buff[i] = ( octet & (mask<<i) ) >> i;
    }
  for ( i = 7 ; i >= 0 ; i-- )
    {
      printf("%d",buff[i]);
    }
  putchar('\n');
}
  



/* 
  Fonction qui s'occupe de la gestion unitaire d'un demi bloc lors d'un tour 
  Utile dans tea_encrypt 
*/
unsigned int key_shuffle_tea(unsigned int key[4],unsigned int demi, unsigned int delta, char test)
{
  unsigned int top;
  unsigned int mid;
  unsigned int bot;
  bot = demi >> 5;
  top = demi << 4;
  if(!test)
  {
    top+=key[0];
    bot+=key[1];

  }
  else
  {
    top += key[2];
    bot += key[3];
  }
  mid = demi + delta;
  return top^mid^bot;
}

/*
  Fonction tea_encrypt
  On lui donne dans un tableau 1 bloc divisé en 2 sous blocs et la clef
*/

void tea_encrypt_bloc(unsigned int tour, unsigned int key[4], unsigned int bloc[2])
{
  unsigned int i;
  unsigned int l = bloc[0];
  unsigned int r = bloc[1];
  unsigned int lpu;
  unsigned int delta = 0x9e3779b9;
  for ( i = 0 ; i < tour ; i++ )
  {
    l += key_shuffle_tea(key,r,delta,0);
    r += key_shuffle_tea(key,l,delta,1);
    delta += delta;
  }
  bloc[0] = l;
  bloc[1] = r;
}

 void tea_decrypt_bloc(unsigned int tour, unsigned int key[4], unsigned int bloc[2])
 {
  unsigned i;
  unsigned l = bloc[0];
  unsigned int r = bloc[1];
  unsigned int lpu;
  unsigned int delta = 0x9e3779b9;
  for ( i = 0 ; i < tour ; i++ )
  {
    l -= key_shuffle_tea(key,r,delta,0);
    r -= key_shuffle_tea(key,l,delta,1);
    delta += delta;
  }
  bloc[0] = l;
  bloc[1] = r;
}

void tea_encrypt_file(char * file_name,unsigned int key[4])
{
  int fd;
  unsigned int b[2];
  int end;
  int err;
  fd = open(file_name,O_CREAT|O_TRUNC|O_RDWR,0644);
  while(1)
  {
    memeset(b, '\0', 8);
    end = read(fd,b,8);
    err = fseek(fd,-2,SEEK_CUR);
    if ( err == -1)
    {
      perror("Erreur lors du fseek ");
      exit(-1);
    }
    if( end <= 0 )
    {
      break;
    }
    tea_encrypt_bloc(32,key,b);
    end = write(fd,b,8);
    if ( end == -1 )
    {
      perror("Erreur lors du write ");
      exit(-1);
    }
  }
  close(fd);
}

void tea_decrypt_file(char * file_name,unsigned int key[4])
{
  int fd;
  unsigned int b[2];
  int end;
  int err;
  fd = open(file_name,O_CREAT|O_TRUNC|O_RDWR,0644);
  while(1)
  {
    memeset(b, '\0', 8);
    end = read(fd,b,8);
    err = fseek(fd,-2,SEEK_CUR);
    if ( err == -1)
    {
      perror("Erreur lors du fseek ");
      exit(-1);
    }
    if( end <= 0 )
    {
      break;
    }
    tea_decrypt_bloc(32,key,b);
    end = write(fd,b,8);
    if ( end == -1 )
    {
      perror("Erreur lors du write ");
      exit(-1);
    }
  }
  close(fd);
}

void get_key_from_file(unsigned short size_key,char * file_name)
{
  if ( size_key < )
}