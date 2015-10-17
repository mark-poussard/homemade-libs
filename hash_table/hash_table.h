#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ABS(a) (((a)>0)?(a):(-(a)))

struct hash_node_t{
  char *id;
  struct hash_node_t *next;
  void *data;
};

struct hash_table_t{
  struct hash_node_t **t;
  int size;

  int (*hash_func)(const char *, int);
};

//------------------------HASH TABLE--------------------------------
struct hash_table_t * hash_table__create(int (*hash_func)(const char *, int), int size);

void hash_table__destroy(struct hash_table_t *table);

void * hash_table__lookup(char *id, struct hash_table_t *table);

int hash_table__insert(struct hash_node_t *n, struct hash_table_t *table);

//------------------------HASH NODE---------------------------------
struct hash_node_t * hash_node__create(const char *id, void *data);

void hash_node__destroy(struct hash_node_t *n);

//------------------------HASH FUNCTIONS----------------------------
int basic_hash_function(const char *id, int size);

//------------------------DEBUG FUNCTIONS---------------------------
void hash_table__dbg__print(struct hash_table_t *table);

#endif
