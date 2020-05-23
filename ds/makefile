#############################################################################
#																			#
#							Author: Sergey Konsta					   		# #							makefile for all DS								#
#							outputs global DS library and 					#
#							exes for every test								#
#																			#
#############################################################################

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -iquote include/
LDFLAGS = -shared

INC_PATH = include/
OBJ_PATH = obj/
TEST_PATH = test/
LIB_PATH = lib/
SRC_PATH = src/

ALL_OBJS = $(notdir $(patsubst %.h,%.o,$(wildcard include/*.h)) )
ALL_OBJS_AND_PATH = $(patsubst include/%.h,obj/%.o,$(wildcard include/*.h))
ALL_SRCS = $(basename $(notdir $(patsubst %.h,%.o,$(wildcard include/*.h)) ) )
ALL_EXES = $(notdir $(patsubst %.c,%.out,$(wildcard test/*.c)) )
ALL_TESTS = $(basename $(notdir $(wildcard test/*.c) ) )

################################################################################
.PHONY: test
test: $(LIB_PATH)libDS.so
	for i in $(ALL_TESTS); \
	do $(CC) $(CFLAGS) -L$(LIB_PATH) -Wl,-rpath=$(LIB_PATH) \
	$^ $(TEST_PATH)$$i.c \
	-o $$i.out \
	-lDS; \
	done; clear; echo "all tests compiled and ready to run, for warnings look up.";

#target is shared library compiled of all Data-Structures objs 
$(LIB_PATH)libDS.so: $(ALL_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(ALL_OBJS_AND_PATH); clear;

$(ALL_OBJS): 
	for i in $(ALL_SRCS); \
	do $(MAKE) ../../$(OBJ_PATH)$$i.o -C $(SRC_PATH)$$i; \
	done

#############################################################################
#									PHONYS									#
#############################################################################
.PHONY: release
release: $(ALL_OBJS)
	$(CC) $(LDFLAGS) -O3 -DNDEBUG -o $(LIB_PATH)libDSRelease.so $(ALL_OBJS_AND_PATH); \
	clear; echo "RELEASE version SO compiled.";

.PHONY: debug
debug: $(ALL_OBJS)
	$(CC) $(LDFLAGS) -o $(LIB_PATH)libDS.so $(ALL_OBJS_AND_PATH); \
	clear; echo "DEBUG version SO compiled.";

.PHONY: all
all: $(ALL_OBJS)
	$(CC) $(LDFLAGS) -O3 -DNDEBUG -o $(LIB_PATH)libDSRelease.so $(ALL_OBJS_AND_PATH); \
	$(CC) $(LDFLAGS) -o $(LIB_PATH)libDS.so $(ALL_OBJS_AND_PATH); \
	clear; echo "DEBUG and RELEASE versions SO compiled";

.PHONY: test
test:

.PHONY: clean
clean : 
	rm $(LIB_PATH)lib*.so *.out $(OBJ_PATH)*.o;
	
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
