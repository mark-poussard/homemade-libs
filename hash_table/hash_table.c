#include "hash_table.h"

//------------------------HASH TABLE--------------------------------
struct hash_table_t * hash_table__create(int (*hash_func)(const char *, int), int size){
  struct hash_table_t *r = malloc(sizeof(*r));
  r->t = malloc(sizeof(*(r->t)) * size);
  for(int i=0; i < size; i++){
    (r->t)[i] = NULL;
  }
  r->size = size;
  r->hash_func = hash_func;
  
  return r;
}

void hash_table__destroy(struct hash_table_t *table){
  for(int i=0; i < table->size; i++){
    if((table->t)[i]){
      hash_node__destroy((table->t)[i]);
      (table->t)[i] = NULL;
    }
  }
  free(table->t);
  free(table);
}

void * hash_table__lookup(char *id, struct hash_table_t *table){
  struct hash_node_t *n = (table->t)[table->hash_func(id, table->size)];
  while(n){
    if(!strcmp(n->id, id))
      return n->data;
    n = n->next;
  }
  return NULL;
}

int hash_table__insert(struct hash_node_t *n, struct hash_table_t *table){
  int hash_r = table->hash_func(n->id, table->size);
  struct hash_node_t *dst = (table->t)[hash_r];
  if(!dst){
    (table->t)[hash_r] = n;
    return 0;
  }
  while(dst->next){
    if(!strcmp(n->id, dst->id))
      return -1;
    dst = dst->next;
  }
  if(!strcmp(n->id, dst->id))
    return -1;
  dst->next = n;

  return 0;
}

//------------------------HASH NODE---------------------------------
struct hash_node_t * hash_node__create(const char *id, void *data){
  struct hash_node_t *r = malloc(sizeof(*r));
  r->id = malloc(strlen(id)+1);
  strcpy(r->id, id);
  r->data = data;
  r->next = NULL;

  return r;
}

void hash_node__destroy(struct hash_node_t *n){
  struct hash_node_t *next = n->next;
  if(next)
    hash_node__destroy(next);
  free(n->id);
  free(n);
}

//------------------------HASH FUNCTIONS----------------------------
int basic_hash_function(const char *id, int size){
  int hashval = 0;
  const char *str = id;
  while(*str){
    hashval = *str + (hashval << 5) - hashval;
    str++;
  }
  return ABS(hashval % size);
}

//------------------------DEBUG FUNCTIONS---------------------------
void hash_table__dbg__print(struct hash_table_t *table){
  for(int i=0; i < table->size; i++){
    struct hash_node_t *n = (table->t)[i];
    fprintf(stderr, "---- Entry n°%d ----\n", i);
    while(n){
      fprintf(stderr, "%s\n\t->%ld\n", n->id, *(long*)n->data);
      n = n->next;
    }
  }
}
