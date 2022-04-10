#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  long aux=hash(key, map->capacity);
  Pair *dato = createPair(key, value);
  while(map->buckets[aux] != NULL){
    aux++;
    if(aux==(map->capacity)){
      aux=0;
    }
  }
  map->current = aux;
  map->buckets[aux]=dato;
  map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *aux=(HashMap*)malloc(sizeof(HashMap));
  aux->buckets=(Pair**)malloc(sizeof(Pair*)*capacity);
  for(int i=0;i<capacity;i++){
    aux->buckets[i]=NULL;
  }
  aux->capacity=capacity;
  aux->size=0;
  aux->current=-1;
    return aux;
}

void eraseMap(HashMap * map,  char * key) { 
  Pair *aux=searchMap(map, key);
  if(aux){
    aux->key=NULL;
    (map->size)--;
  }

}

Pair * searchMap(HashMap * map,  char * key) {   
  long aux=hash(key, map->capacity);
  while(map->buckets[aux] != NULL){
    if(is_equal(map->buckets[aux]->key, key)){
      map->current=aux;
      return map->buckets[aux];
    }
    aux++;
  }
  if(aux > map->capacity){
    return NULL;
  }
  
  return NULL;
}

Pair * firstMap(HashMap * map) {
  long aux=0;
  while(aux < map->capacity){
    if(map->buckets[aux] != NULL && map->buckets[aux]->key != NULL){
      map->current=aux;
      return map->buckets[aux];
    }
    aux++;
  }
    return NULL;
}

Pair * nextMap(HashMap * map) {
  long aux;
  for(aux=map->current+1;aux<map->capacity;aux++){
    if(map->buckets[aux] != NULL){
      map->current=aux;
      return map->buckets[aux];
    }
    
  }
    return NULL;
}
