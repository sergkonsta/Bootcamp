#############################################################################
#																			#
#				makefile for watchdog										#
#																			#
#############################################################################

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS = -shared


.PHONY: run
run: a.out test_dl.so
	./a.out Foo

a.out : dyn_test.c
	$(CC) $(CFLAGS) dyn_test.c -ldl

test_dl.so : test_dl.c
	$(CC) $(LDFLAGS) $^ -o $@



#############################################################################
#									PHONYS									#
#############################################################################


.PHONY: clean
clean : 
	rm *.o *.so *.out

.PHONY: run_client
run_client:
	./client.out ./watchdog_exe.out

.PHONY: vlg
vlg:
	valgrind --leak-check=yes --track-origins=yes ./client.out ./watchdog_exe.out

#update git repository - ABSOLUTE PATH
.PHONY: gitp
gitp:
	cd ~/sergey-konstantinovsky/; git add .; git commit -ma; git push -u; 
