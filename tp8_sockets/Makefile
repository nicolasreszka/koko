All : un_serv_echo_client un_serv_echo_fork un_serv_echo_threads clean 

un_serv_echo_client.o : un_serv_echo_client.c
	gcc -c un_serv_echo_client.c

un_serv_echo_fork.o : un_serv_echo_fork.c
	gcc -c un_serv_echo_fork.c

un_serv_echo_threads.o : un_serv_echo_threads.c
	gcc -c un_serv_echo_threads.c

un_serv_echo_client : un_serv_echo_client.o
	gcc -o un_serv_echo_client un_serv_echo_client.o

un_serv_echo_fork : un_serv_echo_fork.o
	gcc -o un_serv_echo_fork un_serv_echo_fork.o

un_serv_echo_threads : un_serv_echo_threads.o
	gcc -lpthread -o un_serv_echo_threads un_serv_echo_threads.o

clean:
	rm *.o