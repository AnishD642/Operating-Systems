//Including Header File 
#include<iostream>
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
    //Sort the request array in ascending order
    int temp;
    for(int i=0;i<nor-1;i++)
    {
        for(int j=0;j<nor-i-1;j++)
        {
            if(req[j]>req[j+1])
            {
                temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    //index - to store the index of the request just before the head 
    //cond - condition to store the 3 different condition values of the algorithm
    //1 - if the head is anywhere in between the first and last request
    //2 - if the head is in between last request and the end edge 
    //3 - if the head is in between 0 and the first request 
    int index=-1,cond;
    for(int i=0;i<nor;i++)
    {
        if(req[i]<head && req[i+1]>head && i!=nor-1)
        {
            index=i;
            cond=1;
        }
        else if(req[i]<head && i==nor-1)
        {
            index=i;
            cond=2;
        }
        else if(req[i]>head && i==0)
        {
            cond=3;
        }
    }
    //If condition 1
    if(cond==1)
    {
        for(int i=index+1;i<nor;i++)
        {
            // ST from the last request 
            if(i==nor-1)
            {
                tst+=abs(req[i]-(noc-1));
                tst+=abs(req[i]-req[i-1]);
            }
            // ST from index just next to head 
            else if(i==index+1)
            {
                tst+=abs(req[i]-head);
            }
            // ST from the other indexes 
            else
            {
                tst+=abs(req[i]-req[i-1]);
            }
        }
        for(int i=index;i>=0;i--)
        {
            // ST from the index just previous to head 
            if(i==index)
            {
                tst+=abs((noc-1)-req[i]);
            }
            // ST from the other indexes 
            else
            {
                tst+=abs(req[i]-req[i+1]);
            }
        }
    }
    //If condition 2 
    else if(cond==2)
    {
        //From head to the end of the cylinders 
        tst+=abs((noc-1)-head);
        for(int i=nor-1;i>=0;i--)
        {
            // ST for the last request 
            if(i==nor-1)
            {
                tst+=abs(req[i]-(noc-1));
            }
            // ST for the other indexes 
            else
            {
                tst+=abs(req[i+1]-req[i]);
            }
        }
    }
    //If condition 3 
    else
    {
        //From head to the first request 
        tst+=abs(req[0]-head);
        for(int i=1;i<nor;i++)
        {
            //For the other requests 
            tst+=abs(req[i]-req[i-1]);
        }
    }
    //cout<<"Total Seek time (distance):"<<endl;
    cout<<tst<<endl;
}