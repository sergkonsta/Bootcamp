CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DS_INCLUDE=-iquote ds/include/
DS_SRC=ds/src/
DS_TEST=ds/test/


slist: 
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o out $(DS_TEST)slist_test.c $(DS_SRC)slist/slist.c

queue:
	$(CC) $(CFLAGS) $(DS_INCLUDE) -o out $(DS_TEST)queue_test.c $(DS_SRC)queue/queue.c $(DS_SRC)slist/slist.c



vlgg:
	valgrind --leak-check=yes --track-origins=yes ./out




gitpushh:
	git add .; git commit -ma; git push -u;


