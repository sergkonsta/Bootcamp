#############################################################################
#																			#
#				makefile for watchdog										#
#																			#
#############################################################################

NAME = wd
SUB_NAME_1 = heap_pq
SUB_NAME_2 = task
SUB_NAME_3 = uid
SUB_NAME_4 = dynamic_vector
SUB_NAME_5 = heap

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ./include/ -iquote ../../ds/include/
LDFLAGS = -shared

OBJ_PATH = ../../ds/obj/
LIB_PATH = ../../ds/lib/

.PHONY: client
client : lib/libwd_and_utils.so test/client.c
	$(CC) $(CFLAGS) -L./lib -Wl,-rpath=./lib \
	-o client.out $^ \
	-lwd_and_utils -pthread

.PHONY: watchdog_exe
watchdog_exe : src/watchdog_exe.c lib/libwd_utils.so
	$(CC) $(CFLAGS) -L./lib -Wl,-rpath=./lib \
	-o watchdog_exe.out $^ \
	-lwd_utils -pthread

lib/libwd_and_utils.so : obj/wd.o obj/wd_utils.o $(OBJ_PATH)sched.o $(OBJ_PATH)$(SUB_NAME_1).o $(OBJ_PATH)$(SUB_NAME_2).o $(OBJ_PATH)$(SUB_NAME_3).o $(OBJ_PATH)$(SUB_NAME_4).o $(OBJ_PATH)$(SUB_NAME_5).o
	$(CC) $(LDFLAGS) -o $@ $^


lib/libwd_utils.so : obj/wd_utils.o $(OBJ_PATH)sched.o $(OBJ_PATH)$(SUB_NAME_1).o $(OBJ_PATH)$(SUB_NAME_2).o $(OBJ_PATH)$(SUB_NAME_3).o $(OBJ_PATH)$(SUB_NAME_4).o $(OBJ_PATH)$(SUB_NAME_5).o
	$(CC) $(LDFLAGS) -o $@ $^ 


obj/wd.o : src/wd.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^


obj/wd_utils.o : src/wd_utils.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^ 
	

##data structures - utilities

../../ds/obj/sched.o: ../../ds/src/sched/sched.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

../../ds/obj/heap_pq.o: ../../ds/src/heap_pq/heap_pq.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

../../ds/obj/task.o: ../../ds/src/task/task.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^
	
../../ds/obj/uid.o: ../../ds/src/uid/uid.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^
	
../../ds/obj/dynamic_vector.o: ../../ds/src/dynamic_vector/dynamic_vector.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^	

../../ds/obj/heap.o: ../../ds/src/heap/heap.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^
#############################################################################
#									PHONYS									#
#############################################################################


.PHONY: clean
clean : 
	rm obj/*.o lib/*.so ../../ds/obj/*.o

.PHONY: run_client
run_client:
	./client.out

.PHONY: vlg
vlg:
	valgrind --leak-check=yes --track-origins=yes ./client.out ./watchdog_exe.out

#update git repository - ABSOLUTE PATH
.PHONY: gitp
gitp:
	cd ~/sergey-konstantinovsky/; git add .; git commit -ma; git push -u; 
