All : pipe_ex pipe_ex_two_writers clean

pipe_ex.o : pipe_ex.c
	gcc -c pipe_ex.c

pipe_ex : pipe_ex.o
	gcc -o pipe_ex pipe_ex.o

pipe_ex_two_writers.o : pipe_ex_two_writers.c
	gcc -c pipe_ex_two_writers.c

pipe_ex_two_writers : pipe_ex_two_writers.o
	gcc -o pipe_ex_two_writers pipe_ex_two_writers.o

clean:
	rm *.o