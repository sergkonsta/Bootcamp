#############################################################################
#																			#
#							makefile for pqueue								#
#																			#
#############################################################################
#
#	includes dlist obj inside of sorted_list's shared library
#

NAME = pqueue
SUB_NAME_1 = sorted_list
SUB_NAME_2 = dlist

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
$(LIB_PATH)lib$(NAME).so: $(OBJ_PATH)$(NAME).o $(OBJ_PATH)$(SUB_NAME_1).o $(OBJ_PATH)$(SUB_NAME_2).o
	$(CC) $(LDFLAGS) -o $@ $^
	
$(OBJ_PATH)$(NAME).o: $(NAME).c 
	$(CC) $(CFLAGS) -c -fPIC -o $@ $<

#if sub-obj file doesn't exist - go to sub-Make and create it
$(OBJ_PATH)$(SUB_NAME_1).o: 
	$(MAKE) $@ -C ../$(SUB_NAME_1)

#if sub-obj file doesn't exist - go to sub-Make and create it
$(OBJ_PATH)$(SUB_NAME_2).o: 
	$(MAKE) $@ -C ../$(SUB_NAME_2)

#############################################################################
#									PHONYS									#
#############################################################################


.PHONY: clean
clean : 
	rm $(OBJ_PATH)$(NAME).o $(LIB_PATH)lib$(NAME).so $(NAME).out; \
	$(MAKE) clean -C ../$(SUB_NAME_1) 

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
