All : spn_encrypt spn_decrypt clean

spn_encrypt.o : spn_encrypt.c
	gcc -c spn_encrypt.c

spn_decrypt.o : spn_decrypt.c
	gcc -c spn_decrypt.c

spn_encrypt : spn_encrypt.o
	gcc -o spn_encrypt spn_encrypt.o

spn_decrypt : spn_decrypt.o
	gcc -o spn_decrypt spn_decrypt.o

clean:
	rm *.o