#############################################################################
#																			#
#							makefile for UID								#
#																			#
#############################################################################

CC = gcc

CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ../../include
LDFLAGS = -shared

NAME = uid

OBJ = ../../obj/
TEST = ../../test/
LIB = ../../lib/

$(NAME).out : $(LIB)lib$(NAME).so
	$(CC) $(CFLAGS) -L$(LIB) -Wl,-rpath=$(LIB)\
	-o $(NAME).out\
	-l$(NAME)		#assumes all library files start with "lib" end with ".so"

$(LIB)lib$(NAME).so: $(OBJ)$(NAME).o
	$(CC) $(LDFLAGS) -o $(LIB)lib$(NAME).so $^
	
$(OBJ)$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^




#############################################################################
#									PHONYS									#
#############################################################################


.PHONY: clean
clean : 
	rm $(OBJ)$(NAME).o $(LIB)lib$(NAME).so $(NAME).out

.PHONY: cgdb	
cgdb:
	cgdb $(NAME).out

.PHONY: vlg
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(NAME).out
