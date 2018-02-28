All : un_serv_echo_client un_serv_echo_fork clean 

un_serv_echo_client.o : un_serv_echo_client.c
	gcc -c un_serv_echo_client.c

un_serv_echo_fork.o : un_serv_echo_fork.c
	gcc -c un_serv_echo_fork.c

un_serv_echo_client : un_serv_echo_client.o
	gcc -o un_serv_echo_client un_serv_echo_client.o

un_serv_echo_fork : un_serv_echo_fork.o
	gcc -o un_serv_echo_fork un_serv_echo_fork.o

clean:
rm *.o