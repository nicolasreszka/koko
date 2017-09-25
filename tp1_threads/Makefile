All : figure1 figure2 figure3 figure4 figure5 figure6 figure7 show_ids many_threads lead iamzombie generic_server daemon clean

figure1.o : figure1.c
	gcc -c figure1.c

figure2.o : figure2.c
	gcc -c figure2.c

figure3.o : figure3.c
	gcc -c figure3.c

figure4.o : figure4.c
	gcc -c figure4.c

figure5.o : figure5.c
	gcc -c figure5.c

figure6.o : figure6.c
	gcc -c figure6.c

figure7.o : figure7.c
	gcc -c figure7.c

show_ids.o : show_ids.c
	gcc -c show_ids.c

many_threads.o : many_threads.c
	gcc -c many_threads.c

lead.o : lead.c
	gcc -c lead.c

generic_server.o : generic_server.c
	gcc -c generic_server.c

iamzombie.o : iamzombie.c
	gcc -c iamzombie.c

daemon.o : daemon.c
	gcc -c daemon.c

figure1 : figure1.o
	gcc -o figure1 figure1.o

figure2 : figure2.o
	gcc -o figure2 figure2.o

figure3 : figure3.o
	gcc -o figure3 figure3.o

figure4 : figure4.o
	gcc -o figure4 figure4.o

figure5 : figure5.o
	gcc -o figure5 figure5.o

figure6 : figure6.o
	gcc -o figure6 figure6.o

figure7 : figure7.o
	gcc -lpthread -o figure7 figure7.o

show_ids : show_ids.o
	gcc -o show_ids show_ids.o

many_threads : many_threads.o
	gcc -lpthread -o many_threads many_threads.o

lead : lead.o
	gcc -o lead lead.o

iamzombie : iamzombie.o
	gcc -o iamzombie iamzombie.o

generic_server : generic_server.o
	gcc -o generic_server generic_server.o

daemon : daemon.o
	gcc -lpthread -o daemon daemon.o

clean:
	rm *.o