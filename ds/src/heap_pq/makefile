#############################################################################
#																			#
#		makefile for single file project & Dynamic vector subproj			#
#																			#
#############################################################################
SUB_NAME2 = heap
SUB_NAME = dynamic_vector

NAME = $(basename $(notdir $(wildcard *.c)))

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ../../include
LDFLAGS = -shared

OBJ_PATH = ../../obj/
TEST_PATH = ../../test/
LIB_PATH = ../../lib/
SRC_PATH = ../../src/

$(NAME).out : $(LIB_PATH)lib$(NAME).so $(TEST_PATH)$(NAME)_test.c	
	$(CC) $(CFLAGS) -L$(LIB_PATH) -Wl,-rpath=$(LIB_PATH) \
	-o $@ $^ \
	-l$(NAME) -lm

#target is shared library compiled of this projects obj and encapsulated obj
$(LIB_PATH)lib$(NAME).so: $(OBJ_PATH)$(NAME).o $(OBJ_PATH)$(SUB_NAME).o $(OBJ_PATH)$(SUB_NAME2).o
	$(CC) $(LDFLAGS) -o $@ $^ 

$(OBJ_PATH)$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^ 

$(OBJ_PATH)$(SUB_NAME).o: $(SRC_PATH)$(SUB_NAME)/$(SUB_NAME).c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^
	
$(OBJ_PATH)$(SUB_NAME2).o: $(SRC_PATH)$(SUB_NAME2)/$(SUB_NAME2).c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

$(SRC_PATH)$(SUB_NAME)/$(SUB_NAME).c:
	$(CC) $(CFLAGS) -c -fPIC -o $@ 

$(SRC_PATH)$(SUB_NAME2)/$(SUB_NAME2).c:
	$(CC) $(CFLAGS) -c -fPIC -o $@ 
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
