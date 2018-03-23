#Variables

CC = gcc

OFILES = rsa.o \
         elong.o \
         rsa_get_keys.o \
         rsa_encrypt.o \
         rsa_decrypt.o \
    
#Goal

all : rsa_encrypt rsa_decrypt rsa_get_keys clean

#Dependencies

rsa_get_keys.o : rsa.h 

rsa_encrypt.o : elong.h

rsa_decrypt.o : elong.h

#Commands

rsa_get_keys : rsa.o rsa_get_keys.o
	$(CC) -o rsa_get_keys rsa.o rsa_get_keys.o

rsa_encrypt : elong.o rsa_encrypt.o
	$(CC) -o rsa_encrypt elong.o rsa_encrypt.o

rsa_decrypt : elong.o rsa_decrypt.o
	$(CC) -o rsa_decrypt elong.o rsa_decrypt.o

clean :
	-rm -f ${OFILES}