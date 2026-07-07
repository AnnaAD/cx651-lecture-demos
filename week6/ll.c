#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define NUM_THREADS 1000
#define NUM_ITERS 1000


typedef struct Node {
   int data;
   struct Node* next;
} Node;


Node* head = NULL;


void insert_at_head(int value) {
   Node* new_node = malloc(sizeof(Node));
   new_node->data = value;

   new_node->next = head;
   head = new_node;
}


void* thread_func(void* arg) {
   for(int i = 0; i < NUM_ITERS; i++) {
     insert_at_head(*(int*)arg);
   }
   return NULL;
}


int main() {
   pthread_t threads[NUM_THREADS];
   int ids[NUM_THREADS];


   for (int i = 0; i < NUM_THREADS; i++) {
       ids[i] = i;
       pthread_create(&threads[i], NULL, thread_func, &ids[i]);
   }


   for (int i = 0; i < NUM_THREADS; i++)
       pthread_join(threads[i], NULL);


   int length = 0;
   Node* current = head;
   while (current) {
       length++;
       current = current->next;
   }


   printf("Final list length: %d (expected %d)\n", length, NUM_THREADS*NUM_ITERS);


   return 0;
}
