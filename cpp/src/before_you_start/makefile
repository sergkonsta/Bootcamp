#############################################################################
#																			#
#				makefile for watchdog										#
#																			#
#############################################################################

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS = -shared


.PHONY: run
run: a.out test_dl.o
	./a.out Foo

a.out : dyn_test.c
	$(CC) $(CFLAGS) dyn_test.c -ldl

test_dl.o : test_dl.c
	$(CC) $(LDFLAGS) -fPIC $^ -o $@



#############################################################################
#									PHONYS									#
#############################################################################


.PHONY: clean
clean : 
	rm *.o *.so *.out

.PHONY: vlg
vlg:
	valgrind --leak-check=yes --track-origins=yes ./a.out Foo

#update git repository - ABSOLUTE PATH
.PHONY: gitp
gitp:
	cd ~/sergey-konstantinovsky/; git add .; git commit -ma; git push -u; 
