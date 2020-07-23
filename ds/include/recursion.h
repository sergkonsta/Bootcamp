#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "slist.h"
#include "stack.h"

/*for slist*/
struct slist_node
{
  void *data;
  struct slist_node *next;
};

int FibNotTailRec(int elem_index);
int FibonacciRecursive(int elem_index);
int FibonacciIterative(int elem_index);

size_t StrLenRecursive(const char *str);
char *StrCpyRecursive(char *dest, const char *src);
char *StrCpyTailRecursive(char *dest, const char *src);
char *StrCatRecursive(char *dest, const char *src);
char *StrStrRecursive(const char *haystack, const char *needle);
int StrCmpTailRecursive(const char *str1, const char *str2);

slist_iter_t FlipList(slist_iter_t node);

stack_t *SortStack(stack_t *stk);

#endif 
