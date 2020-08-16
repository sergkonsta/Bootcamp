#############################################################################
#																			#
#							makefile for SCHED								#
#																			#
#############################################################################


NAME = $(basename $(notdir $(wildcard *.c)))

SUB_NAME_1 = heap_pq
SUB_NAME_2 = task
SUB_NAME_3 = uid
SUB_NAME_4 = dynamic_vector
SUB_NAME_5 = heap
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
$(LIB_PATH)lib$(NAME).so: $(OBJ_PATH)$(NAME).o $(OBJ_PATH)$(SUB_NAME_1).o $(OBJ_PATH)$(SUB_NAME_2).o $(OBJ_PATH)$(SUB_NAME_3).o $(OBJ_PATH)$(SUB_NAME_4).o $(OBJ_PATH)$(SUB_NAME_5).o
	$(CC) $(LDFLAGS) -o $@ $^
	
$(OBJ_PATH)$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

#if sub-obj file doesn't exist - go to sub-Make and create it
$(OBJ_PATH)$(SUB_NAME_1).o: 
	$(MAKE) -C ../$(SUB_NAME_1)/$(SUB_NAME_1).c

#if sub-obj file doesn't exist - go to sub-Make and create it
$(OBJ_PATH)$(SUB_NAME_2).o: 
	$(MAKE) -C ../$(SUB_NAME_2)/$(SUB_NAME_2).c

#if sub-obj file doesn't exist - go to sub-Make and create it
$(OBJ_PATH)$(SUB_NAME_3).o: 
	$(MAKE) -C ../$(SUB_NAME_3)/$(SUB_NAME_3).c

#if sub-obj file doesn't exist - go to sub-Make and create it
$(OBJ_PATH)$(SUB_NAME_4).o: 
	$(MAKE) -C ../$(SUB_NAME_4)/$(SUB_NAME_4).c
	
#if sub-obj file doesn't exist - go to sub-Make and create it
$(OBJ_PATH)$(SUB_NAME_5).o: 
	$(MAKE) -C ../$(SUB_NAME_5)/$(SUB_NAME_5).c

	



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
	cd ~/bootcamp/; git add .; git commit -ma; git push -u; 
