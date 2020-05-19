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

INC_PATH = include/
OBJ_PATH = obj/
TEST_PATH = test/
LIB_PATH = lib/

#get a list of all DS obj files:  var = [ filter ir(.h files changed to .o) ]
ALL_OBJS = $(notdir $(patsubst %.h,%.o,$(wildcard include/*.h)) )


ALL_SRCS = $(basename $(notdir $(patsubst %.h,%.o,$(wildcard include/*.h)) ) )
	
#target is shared library compiled of all ds objs 
$(LIB_PATH)libDS.so: $(ALL_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(ALL_OBJS): 
	for target in "$(ALL_SRCS)"; do $(MAKE) -C $$target; done

# rule to generate a dep file by using the C preprocessor
%.d: %.c
	@$(CC) $(CFLAGS) $< -MM -MT $(ALL_OBJS) >$@


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
