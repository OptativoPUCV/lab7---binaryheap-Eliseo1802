#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

void* heap_top(Heap* pq){
  void* pr = pq->heapArray[0].data;
  if(pq->size==0) return NULL;
  return pr;
}

void reorderHeap(Heap* pq, int index){
  int parent = (index-1)/2;
  int aux;

  if (pq->heapArray[parent].priority >= pq->heapArray[index].priority)
    return;
  else{
    aux = pq->heapArray[parent].priority;
    pq->heapArray[parent].priority = pq->heapArray[index].priority;
    pq->heapArray[index].priority = aux;
    reorderHeap(pq, parent);
  }
}

void heap_push(Heap* pq, void* data, int priority){
  if(pq->size==pq->capac){
    pq->heapArray = realloc(pq->heapArray,sizeof(heapElem)*(pq->capac*2+1));
    pq->capac*=2;
  }
  pq->size++;
  
  pq->heapArray[pq->size-1].data = data;
  pq->heapArray[pq->size-1].priority = priority;
  reorderHeap(pq, pq->size-1);
}

void heap_pop(Heap* pq){

}

Heap* createHeap(){
  Heap* new = (Heap*)malloc(sizeof(Heap));
  new->size = 0;
  new->capac = 3;
  new->heapArray = (heapElem*)calloc(new->capac,sizeof(heapElem));

  return new;
}