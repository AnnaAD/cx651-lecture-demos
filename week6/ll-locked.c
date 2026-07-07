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
pthread_mutex_t lock;


void insert_at_head(int value) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = value;

    pthread_mutex_lock(&lock);
    new_node->next = head;
    head = new_node;
    pthread_mutex_unlock(&lock);
}


void* thread_func(void* arg) {
   for(int i = 0; i < NUM_ITERS; i++) {
     insert_at_head(*(int*)arg);
   }
   return NULL;
}


int main() {

    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("Mutex initialization failed.\n"); 
        return 1; 
    } 

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

   pthread_mutex_destroy(&lock); 


   return 0;
}
