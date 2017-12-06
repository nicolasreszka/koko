All : tcp_client_dialog_simple tcp_server_echo_fork clean

tcp_client_dialog_simple.o : tcp_client_dialog_simple.c
	gcc -c tcp_client_dialog_simple.c

tcp_client_dialog_simple : tcp_client_dialog_simple.o
	gcc -o tcp_client_dialog_simple tcp_client_dialog_simple.o

tcp_server_echo_fork.o : tcp_server_echo_fork.c
	gcc -c tcp_server_echo_fork.c

tcp_server_echo_fork : tcp_server_echo_fork.o
	gcc -o tcp_server_echo_fork tcp_server_echo_fork.o

clean:
	rm *.o
