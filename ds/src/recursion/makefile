#############################################################################
#																			#
#	makefile for single file project & stack, s-list subprojs				#
#																			#
#############################################################################

NAME = $(basename $(notdir $(wildcard *.c)))

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ../../include
LDFLAGS = -shared

OBJ_PATH = ../../obj/
TEST_PATH = ../../test/
LIB_PATH = ../../lib/

$(NAME).out : $(LIB_PATH)lib$(NAME).so $(TEST_PATH)$(NAME)_test.c	
	$(CC) $(CFLAGS) -L$(LIB_PATH) -Wl,-rpath=$(LIB_PATH) \
	-o $@ $^ \
	-l$(NAME)

#target is shared library compiled of this projects obj and encapsulated obj
$(LIB_PATH)lib$(NAME).so: $(OBJ_PATH)$(NAME).o $(OBJ_PATH)stack.o $(OBJ_PATH)slist.o
	$(CC) $(LDFLAGS) -o $@ $^ 

$(OBJ_PATH)$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^ 

$(OBJ_PATH)stack.o:
	$(CC) $(CFLAGS) -c -fPIC -o $@ ../../src/stack/stack.c
	
$(OBJ_PATH)slist.o:
	$(CC) $(CFLAGS) -c -fPIC -o $@ ../../src/slist/slist.c
#############################################################################
#									PHONYS									#
#############################################################################


.PHONY: clean
clean : 
	rm $(OBJ_PATH)$(NAME).o $(LIB_PATH)lib$(NAME).so $(NAME).out; \

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
