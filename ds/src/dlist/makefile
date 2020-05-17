CC = gcc

CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ../../include
LDFLAGS = -shared

NAME = dlist

SRC = $(NAME).c
OBJ = ../../obj/
TEST = ../../test/$(NAME)_test.c
LIB = ../../lib/

dlist : $(LIB) $(TEST)	
	$(CC) $(CFLAGS) -L$(LIB) -Wl,-rpath=$(LIB) -o $(NAME).out $(TEST) -ldlist

libdlist.so: $(OBJ)$(NAME).o
	$(CC) $(LDFLAGS) -o $(LIB)lib$(NAME).so $^
	
dlist.o: $(NAME).c
	$(CC) $(CFLAGS) -c -fPIC -o $(OBJ)$(NAME).o $^

.PHONY: clean
clean : 
	rm $(OBJ)$(NAME).o $(LIB)lib$(NAME).so) dlist.out
