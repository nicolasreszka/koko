all : print_word_letter_by_letter print_word_letter_by_letter_semaphores clean

print_word_letter_by_letter.o : print_word_letter_by_letter.c
	gcc -c print_word_letter_by_letter.c

print_word_letter_by_letter : print_word_letter_by_letter.o
	gcc -o print_word_letter_by_letter print_word_letter_by_letter.o

print_word_letter_by_letter_semaphores.o : print_word_letter_by_letter_semaphores.c
	gcc -g -c print_word_letter_by_letter_semaphores.c

print_word_letter_by_letter_semaphores : print_word_letter_by_letter_semaphores.o
	gcc -g -o print_word_letter_by_letter_semaphores print_word_letter_by_letter_semaphores.o

exercice_1_a :
	./print_word_letter_by_letter first 100 & ./print_word_letter_by_letter second 20 & ./print_word_letter_by_letter third 200

exercice_1_c :
	./print_word_letter_by_letter_semaphores first 100 1 2 & ./print_word_letter_by_letter_semaphores second 20 2 3 & ./print_word_letter_by_letter_semaphores third 200 3 1

clean:
	rm *.o