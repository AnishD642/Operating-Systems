//Including Header Files 
#include<iostream>
//For mathematical computations 
#include<cmath>
using namespace std;
//Main function 
int main()
{
    //Declaring variables 
    int noc,nor,head;
    //cout<<"Total Number of Cylinders:"<<endl;
    cin>>noc; //User input 
    //cout<<"Current Head Position:"<<endl;
    cin>>head; //User input
    //cout<<"Number of request"<<endl;
    cin>>nor; //User input 
    //Request array 
    int req[nor];
    //cout<<"Queue of pending request"<<endl;
    for(int i=0;i<nor;i++)
    {
        //Traverse to obtain the input values 
        cin>>req[i];
    }
    //Initial Total seek time = 0
    int tst=0;
    for(int i=0;i<nor;i++)
    {
        //Initially, from head to the first request
        //in the array 
        if(i==0)
        {
            //Adding the absolute value 
            tst+=abs(req[i]-head);
        }
        //For other iterations
        //moving from one request to the next request in the queue 
        else
        {
            //Absolute values 
            tst+=abs(req[i]-req[i-1]);
        }
    }
    //Display output 
    //cout<<"Total Seek time (distance):"<<endl;
    cout<<tst<<endl;
}