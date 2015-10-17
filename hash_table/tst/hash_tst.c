#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "../hash_table.h"

#define NB_HASH_T 5
#define NB_DATA 1000
#define HASH_TABLE_SIZE 300

int string_already_exists(char *data_id[], int i){
  for(int j=0; j<i; j++){
    if(!strcmp(data_id[j], data_id[i]))
      return 1;
  }
  return 0;
}

int main(int argc, char**argv){
  struct hash_table_t *my_hash_t[NB_HASH_T];
  long int data[NB_DATA];
  char *data_id[NB_DATA];
  struct hash_node_t *data_nodes[NB_DATA];
  srandom(time(NULL));
  for(int i=0; i < NB_HASH_T; i++){
    my_hash_t[i] = hash_table__create(basic_hash_function, HASH_TABLE_SIZE*(i+1));
    assert(my_hash_t[i] != NULL);
  }
  for(int i=0; i < NB_DATA; i++){
    int size = (random() % 20) +1;
    data_id[i] = malloc(size+1);
    do{
      for(int j=0; j < size; j++){
	*((data_id[i])+j) = (char)((random() % 90)+33);
      }
      *((data_id[i])+size) = 0;
    }while(string_already_exists(data_id, i));
    data[i] = random();
    hash_table__insert(data_nodes[i] = hash_node__create(data_id[i], (void *)&(data[i])), my_hash_t[0]);
  }

  //hash_table__dbg__print(my_hash_t[0]);
  for(int i=0; i < NB_DATA; i++){
    if(!(data[i] == *(int*)hash_table__lookup(data_id[i], my_hash_t[0]))){
      fprintf(stderr, "Test failed on n°%d.\n", i);
      fprintf(stderr, "Hash lookup : %ld\n", *(long*)hash_table__lookup(data_id[i], my_hash_t[0]));
      fprintf(stderr, "Saved value : %ld\n", data[i]);
      fprintf(stderr, "Data from node :\n");
      fprintf(stderr, "\tid : %s | data : %ld | next : %p\n", data_nodes[i]->id, *(long*)data_nodes[i]->data, (void*)data_nodes[i]->next);
    }
  }

  for(int i=0; i < NB_HASH_T; i++){
    hash_table__destroy(my_hash_t[i]);
  }
  for(int i=0; i < NB_DATA; i++)
    free(data_id[i]);
  return 0;
}
