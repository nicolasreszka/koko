All : demo_inet_pton demo_inet_ntop clean

demo_inet_pton.o : demo_inet_pton.c
	gcc -c demo_inet_pton.c

demo_inet_pton : demo_inet_pton.o
	gcc -o demo_inet_pton demo_inet_pton.o

demo_inet_ntop.o : demo_inet_ntop.c
	gcc -c demo_inet_ntop.c

demo_inet_ntop : demo_inet_ntop.o
	gcc -o demo_inet_ntop demo_inet_ntop.o

clean:
	rm *.o
