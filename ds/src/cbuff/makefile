#############################################################################
#																			#
#							makefile for circular buffer					#
#																			#
#############################################################################
#
#	includes dlist obj inside of sorted_list's shared library
#

NAME = cbuff


#
#			DON'T CHANGE FROM HERE!!!
#

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ../../include
LDFLAGS = -shared

OBJ_PATH = ../../obj/
TEST_PATH = ../../test/
LIB_PATH = ../../lib/

$(NAME).out : $(LIB_PATH)lib$(NAME).so $(TEST_PATH)$(NAME)_test.c	
	$(CC) $(CFLAGS) -L$(LIB_PATH) -Wl,-rpath=$(LIB_PATH) \
	-o $@ $^ \
	-l$(NAME) #assumes all library files start with "lib" end with ".so"

#target is shared library compiled of this projects obj and encapsulated obj
$(LIB_PATH)lib$(NAME).so: $(OBJ_PATH)$(NAME).o 
	$(CC) $(LDFLAGS) -o $@ $^
	
$(OBJ_PATH)$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^



#############################################################################
#									PHONYS									#
#############################################################################


.PHONY: clean
clean : 
	rm $(OBJ_PATH)$(NAME).o $(LIB_PATH)lib$(NAME).so *.out;
	

.PHONY: cgdb	
cgdb:
	cgdb $(NAME).out

.PHONY: vlg
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(NAME).out
	
#update git repository - ABSOLUTE PATH
.PHONY: gitp
gitp:
	cd ~/sergey-konstantinovsky/; git add .; git commit -ma; git push -u; 
