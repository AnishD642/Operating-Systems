//Including Header Files 
#include<stdio.h>
//Implementing pthreads 
#include<pthread.h>
//Implementing semaphore operations
#include<semaphore.h>
//Non-zero value implies the semaphore is 
//shared between the processes 
#define share_sema 1
//Producer Function Declaration 
void *producer();
//Consumer Function Declaration 
void *consumer();
//Semaphore variables declaration 
//Data type for semaphore
sem_t empty,full,mutex;
//Data Variables declaration 
int item;
//Assumption - 1 Producer and 1 Consumer 
//Main function
int main()
{
    //Data type for a thread 
    //producer and consumer process thread IDs 
    pthread_t pid,cid; 
    printf("Start\n");
    //Initializing semaphores 
    //first parameter - semaphore to be used
    //second parameter - specifies that the semaphore is to be used
    //between processes (non-zero value)
    //third parameter - value assigned to semaphore
    //Assumed size of buffer - 5
    sem_init(&empty,share_sema,5); 
    //Initial assumption - no item in buffer 
    sem_init(&full,share_sema,0);
    //Initial value of mutex - 1
    sem_init(&mutex,share_sema,1);
    //Creating new threads
    //first parameter - points to the thread id 
    //second parameter - structure defining thread attributes
    //third parameter - function to be executed by the thread
    //fourth parameter - arguments to the function 
    pthread_create(&pid,NULL,producer,NULL);
    pthread_create(&cid,NULL,consumer,NULL);
    //Waiting for the termination of a thread
    //Thread ID, location of the exit status of the thread
    pthread_join(pid,NULL);
    pthread_join(cid,NULL);
    printf("Done\n");
}
//Producer function definition 
void *producer()
{
    //To store the produced item 
    int item_produced;
    printf("Producer process\n");
    //Display Producer Thread ID
    printf("Producer ID is : %ld\n",pthread_self());
    //Loop over to produce items 
    for(item_produced=0;item_produced<5;item_produced++)
    {
        //Entry section
        sem_wait(&empty); //Check and decrement
        sem_wait(&mutex); //mutex becomes 0
        //implying shared variable is being used by the process 
        //No other process allowed to execute
        //Critical section 
        item=item_produced;
        //Exit section 
        sem_post(&mutex); //Mutex becomes 1, allowing other processes 
        sem_post(&full); //Increment indicating one item produced
        printf("Produced : %d\n",item); //Display produced item 
    }
}
//Consumer function definition 
void *consumer()
{
    //To store the item consumed
    int item_consumed;
    printf("Consumer process\n");
    //Display Consumer Thread ID
    printf("Consumer ID is : %ld\n",pthread_self());
    //Loop over to consume items 
    for(item_consumed=0;item_consumed<5;item_consumed++)
    {
        //Entry section
        sem_wait(&full); //Check and decrement 
        sem_wait(&mutex); //mutex 0, other process not allowed 
        //Critical section
        item=item_consumed;
        //Exit section
        sem_post(&mutex); //Mutex becomes 1, allowing other processes 
        sem_post(&empty); //Increment indicating one item consumed
        printf("Consumed : %d\n",item); //Display consumed item
    }
}