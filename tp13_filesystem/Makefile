All : make_sparse clean

make_sparse.o : make_sparse.c
	gcc -c make_sparse.c

make_sparse : make_sparse.o
	gcc -o make_sparse make_sparse.o

clean:
	rm *.o
