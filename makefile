CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DS_INCLUDE=-iquote ds/include/
DS_OBJ=ds/obj/
DS_SRC=ds/src/
DS_TEST=ds/test/

#-------------------------------DATA STRUCTURES--------------------------------#
slist: 
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)slist_test.c $(DS_SRC)slist/slist.c

queue:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)queue_test.c $(DS_SRC)queue/ queue.c	$(DS_SRC)slist/slist.c

cbuff:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)cbuff_test.c $(DS_SRC)cbuff/cbuff.c

dlist:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)dlist_test.c $(DS_SRC)dlist/dlist.c
	
sorted_list:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)sorted_list_test.c $(DS_SRC)sorted_list/sorted_list.c $(DS_SRC)dlist/dlist.c
	
uid:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)uid_test.c $(DS_SRC)uid/uid.c
	
pqueue:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)pqueue_test.c $(DS_SRC)pqueue/pqueue.c $(DS_SRC)sorted_list/sorted_list.c $(DS_SRC)dlist/dlist.c
	
sched:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o $(DS_OBJ)a.out $(DS_TEST)sched_test.c $(DS_SRC)sched/sched.c $(DS_SRC)task/task.c $(DS_SRC)uid/uid.c $(DS_SRC)pqueue/pqueue.c $(DS_SRC)sorted_list/sorted_list.c $(DS_SRC)dlist/dlist.c
	
#-------------------------------GLOBALS----------------------------------------#
cgdb_ds:
	cgdb $(DS_OBJ)a.out

vlg_ds:
	valgrind --leak-check=yes --track-origins=yes ./$(DS_OBJ)a.out

#update git repository
gitp:
	git add .; git commit -ma; git push -u; 


