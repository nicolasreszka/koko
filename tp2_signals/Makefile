All : alive send_signal clean

alive.o : alive.c
	gcc -c alive.c

send_signal.o : send_signal.c
	gcc -c send_signal.c

alive : alive.o
	gcc -o alive alive.o

send_signal : send_signal.o
	gcc -o send_signal send_signal.o

clean:
	rm *.o
