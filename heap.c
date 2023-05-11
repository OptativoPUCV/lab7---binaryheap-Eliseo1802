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

void swap(heapElem *arr, int i1, int i2){
  heapElem aux = arr[i2];
  arr[i2] = arr[i1];
  arr[i1] = aux;
}

void reorderHeapUp(Heap* pq, int index){
  int parent = (index-1)/2;
  int aux;

  if (pq->heapArray[parent].priority >= pq->heapArray[index].priority)
    return;
  else{
    aux = pq->heapArray[parent].priority;
    pq->heapArray[parent].priority = pq->heapArray[index].priority;
    pq->heapArray[index].priority = aux;
    reorderHeapUp(pq, parent);
  }
}

void heap_push(Heap* pq, void* data, int priority){
  if(pq->size==pq->capac){
    pq->heapArray = realloc(pq->heapArray,sizeof(heapElem)*pq->capac*2);
    pq->capac = pq->capac*2+1;
  }
  pq->size++;
  
  pq->heapArray[pq->size-1].data = data;
  pq->heapArray[pq->size-1].priority = priority;
  reorderHeapUp(pq, pq->size-1);
}

void reorderHeapDown(Heap* pq, int index){
  int left,right;
  left = (2*index)+1;
  right = (2*index)+2;
  
  //if(left<pq->size && right<pq->size)
    //return;

  if(pq->heapArray[left].priority>pq->heapArray[index].priority){
    swap(pq->heapArray, left, index);
    reorderHeapDown(pq,index);
  }
  else if (pq->heapArray[right].priority>pq->heapArray[index].priority){
    swap(pq->heapArray, right, index);
    reorderHeapDown(pq,index);
  }
  else return;
}

void heap_pop(Heap* pq){
  swap(pq->heapArray,0,pq->size-1);
  reorderHeapDown(pq,0);
  pq->size--;
}

Heap* createHeap(){
  Heap* new = (Heap*)malloc(sizeof(Heap));
  new->size = 0;
  new->capac = 3;
  new->heapArray = (heapElem*)calloc(new->capac,sizeof(heapElem));

  return new;
}