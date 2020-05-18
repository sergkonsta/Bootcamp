#############################################################################
#																			#
#							makefile for all DS								#
#																			#
#############################################################################
#
#	includes dlist obj inside of sorted_list's shared library
#

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ../../include
LDFLAGS = -shared

#where to search for targets and prerequisites
VPATH = src:include:obj:test:lib

INC_PATH = include/
OBJ_PATH = obj/
TEST_PATH = test/
LIB_PATH = lib/

#get a list of all DS obj files
ALL_OBJS = $(patsubst %.h,%.o,$(wildcard include/*.h))
#ALL_OBJS = include/(wildcard *.h:.h=.o)

%.out : lib%.so %_test.c	
	$(CC) $(CFLAGS) -L$(LIB_PATH) -Wl,-rpath=$(LIB_PATH) \
	-o $@ $^ \
	-l% #assumes all library files start with "lib" end with ".so"

#target is shared library compiled of this projects obj and encapsulated obj
$(LIB_PATH)lib$(NAME).so: $(OBJ_PATH)$(NAME).o $(ALL_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

#general rule for any obj inside ALL_OBJS ?????????????
%.o: %.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

#if sub-obj file doesn't exist - go to sub-Make and create it
$%.o: 
	$(MAKE) -C src/$@





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
