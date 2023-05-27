//Including Header Files 
#include<stdio.h>
//Implementing pthreads 
#include<pthread.h>
//Implementing semaphore operations
#include<semaphore.h>
//Non-zero value implies the semaphore is 
//shared between the processes 
#define share_sema 1
//Reader Function Declaration 
void *reader();
//Writer Function Declaration 
void *writer();
//Semaphore variables declaration 
//Data type for semaphore
sem_t wrt,mutex;
//Data variables declaration
//read_count to count the number of readers 
int read_count=0;
//To store the data to be read/updated 
//Initial value of data is 1
int data=1,init_data;
//Assumption - 2 Readers and 1 Writer
//Main function
int main()
{
    //Data type for a thread 
    //2 Reader process Thread IDs and 1 Writer process Thread ID 
    pthread_t rid1,rid2,wid;
    printf("Start\n");
    //Initializing semaphores 
    //first parameter - semaphore to be used
    //second parameter - specifies that the semaphore is to be used
    //between processes (non-zero value)
    //third parameter - value assigned to semaphore
    sem_init(&wrt,share_sema,1);
    sem_init(&mutex,share_sema,1);
    //Creating new threads
    //first parameter - points to the thread id 
    //second parameter - structure defining thread attributes
    //third parameter - function to be executed by the thread
    //fourth parameter - arguments to the function
    pthread_create(&rid1,NULL,reader,NULL);
    pthread_create(&wid,NULL,writer,NULL);
    pthread_create(&rid2,NULL,reader,NULL);
    //Waiting for the termination of a thread
    //Thread ID, location of the exit status of the thread
    pthread_join(rid1,NULL);
    pthread_join(wid,NULL);
    pthread_join(rid2,NULL);
    printf("Done\n");
}
//Writer process definition 
void *writer()
{
    printf("Writer Process");
    //Display Writer Thread ID
    printf("Writer ID is : %ld\n",pthread_self());
    //Entry section 
    sem_wait(&wrt); //Check and decrement 
    //Lock 
    //Critical section 
    init_data=data; //Initial data value 
    data=data+2; //Updating data
    //Display result 
    printf("Writer updated the data from %d to %d\n",init_data,data); 
    //Exit section 
    sem_post(&wrt); //Increment 
    //Unlock
    printf("\n");
}
//Reader process definition
void *reader()
{
    printf("Reader Process");
    //Display Reader Thread ID
    printf("Reader ID is : %ld\n",pthread_self());
    //Entry section 
    //Process gets locked 
    sem_wait(&mutex);
    //Critical section 
    read_count++;
    if(read_count==1)
    {
        sem_wait(&wrt); //Check and decrement 
        //Writer process not allowed to execute, made to wait 
    }
    //Exit section 
    sem_post(&mutex); //Increment 
    //Lock released 
    //Reading data 
    printf("Reader process read the data. The data is : %d.\n",data);
    //Entry section
    sem_wait(&mutex); //Check and decrement 
    //Process locked 
    //Critical section 
    read_count--; //Reader process ends reading operation 
    if(read_count==0) //If no reader inside critical section 
    {
        sem_post(&wrt); //Increment
        //Allow writer process 
    }
    //Exit section 
    sem_post(&mutex); //Increment 
    //Lock released 
    printf("\n");
}