All : tea_encrypt tea_decrypt clean

tea_encrypt.o : tea_encrypt.c
	gcc -c tea_encrypt.c

tea_decrypt.o : tea_decrypt.c
	gcc -c tea_decrypt.c

tea_encrypt : tea_encrypt.o
	gcc -o tea_encrypt tea_encrypt.o

tea_decrypt : tea_decrypt.o
	gcc -o tea_decrypt tea_decrypt.o

clean:
	rm *.o