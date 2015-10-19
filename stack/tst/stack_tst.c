#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../stack.h"

#define DEFAULT_MOD_VAL 10000

int main(int argc, char**argv){
  srand(time(NULL));
  stack_t *s = stack__create();
  int char_n = rand()%100;
  int int_n  = rand()%100;
  int long_n = rand()%100;
  char *char_a = malloc(sizeof(*char_a)*char_n);
  int *int_a = malloc(sizeof(*int_a)*int_n);
  long *long_a = malloc(sizeof(*long_a)*long_n);
  for(int i=0; i<char_n; i++){
    char_a[i] = rand()%DEFAULT_MOD_VAL;
    stack__push(char_a+i, s);
  }
  for(int i=0; i<int_n; i++){
    int_a[i] = rand()%DEFAULT_MOD_VAL;
    stack__push(int_a+i, s);
  }
  for(int i=0; i<long_n; i++){
    long_a[i] = rand()%DEFAULT_MOD_VAL;
    stack__push(long_a+i, s);
  }
  for(int i=long_n-1; i >= 0; i--){
    assert(long_a[i] == *(long*)(stack__pop(s)));
  }
  for(int i=int_n-1; i >= 0; i--){
    assert(int_a[i] == *(int*)(stack__pop(s)));
  }
  for(int i=char_n-1; i >= 0; i--){
    assert(char_a[i] == *(char*)(stack__pop(s)));
  }
  free(char_a);
  free(int_a);
  free(long_a);
  stack__destroy(s);
}
