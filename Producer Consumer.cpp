//Include Header File
#include<iostream>
using namespace std;
//Function definition for wait() operation 
void wait(int &s)//Passing the semaphore 
{
    //If the value of semaphore is <=0
    //then it goes into an infinite loop 
    while(s<=0); 
    //Decrement if semaphore is greater than 0 
    s--;
}
//Function definition for signal() operation 
void signal(int &s)//Passing the semaphore 
{
    s++; //Incrementing the semaphore value 
}
//Main function 
int main()
{
    //Initializing variables 
    int size,ch;
    char next_produced,next_consumed;
    cout<<"Enter the size of the buffer : "<<endl;
    cin>>size; //User input size
    //Initializing bounded-buffer array 
    char buffer[size]; 
    //The default values of the semaphores 
    int empty=size;
    int full=0;
    int mutex=1;
    //Option variable 
    char op='Y';
    //While option is Yes 
    while(op=='Y')
    {
        //Display statements
        cout<<"1. Produce an item"<<endl;
        cout<<"2. Consume an item"<<endl;
        cout<<"Enter the choice"<<endl;
        cin>>ch; //User input choice 
        switch(ch) //Switch case 
        {
            //Producer Process 
            case 1:
            //If the buffer is partially empty or fully empty and
            //the shared variable isn't being used by other process 
                if(empty!=0 && mutex==1)
                {
                    cout<<"Enter the item"<<endl; 
                    cin>>next_produced; //Produce an item 
                    //Entry section 
                    wait(empty); //Check and decrement 
                    wait(mutex); //mutex becomes 0 
                    //indicating the shared variable is 
                    //being used by this process 
                    //and no other process allowed to execute 
                    //Critical section 
                    //Add produced item to buffer 
                    buffer[full]=next_produced; 
                    //Display the produced item
                    cout<<"The item produced is "<<next_produced<<endl;
                    //Exit section 
                    signal(mutex); //mutex becomes 1 
                    //thus allowing other processes 
                    signal(full); //Increment 
                    //Implying an item is produced and added 
                }
                //If the buffer is full 
                else
                {
                    cout<<"Buffer is full"<<endl;
                }
                break; //End process 
            //Consumer process 
            case 2:
            //If the buffer is partially full or completely full 
            //and the shared variable isn't being used by other process 
                if(full>0 && mutex==1)
                {
                    //Entry section 
                    wait(full); //Check and decrement 
                    wait(mutex); //mutex becomes 0 
                    //Critical section
                    //Remove an item from buffer to next_consumed 
                    next_consumed=buffer[full];
                    //Exit section 
                    signal(mutex); //mutex becomes 1
                    signal(empty); //Increment 
                    //Implying an item is consumed and removed 
                    //Display the consumed item 
                    cout<<"The consumed item is : "<<next_consumed<<endl;
                }
                //If the buffer is empty 
                else
                {
                    cout<<"Buffer is empty"<<endl;
                }
                break; //End process
            //If not a valid choice 
            default:
                cout<<"Wrong Input"<<endl;
        }
        //Option to continue 
        cout<<"\nEnter Y to continue or N to end the operations"<<endl;
        cin>>op;
    }
}