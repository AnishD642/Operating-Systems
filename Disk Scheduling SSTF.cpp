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
    //service array - to obtain the order in which requests are serviced
    //ss - service array size  
    int service[nor],ss=0;
    int min=1000000;
    //Obtain the first request to be serviced 
    for(int i=0;i<nor;i++)
    {
        //Find the minimum distance from the head 
        if(abs(req[i]-head)<min)
        {
            min=abs(req[i]-head); //Min distance 
            service[0]=req[i]; //Add it to the service array 
            //Indicating it has been serviced 
            ss=1; //Increment service array size 
        }
    }
    //Loop over for remaining n-1 requests 
    for(int i=0;i<nor-1;i++)
    {
        min=1000000;
        //Find the minimum distance among all the remaining requests 
        for(int j=0;j<nor;j++)
        {
            if(abs(service[ss-1]-req[j])<min)
            {
                //Make sure the request is not serviced already 
                int flag=0;
                for(int k=0;k<ss;k++)
                {
                    if(service[k]==req[j])
                    {
                        flag=1;
                    }
                }
                //If the distance is minimum 
                //and not in the service array 
                //then that is the minimum distance among the 
                //remaining requests 
                if(flag==0)
                {
                    min=abs(service[ss-1]-req[j]);
                }
            }
        }
        //Find the request which has this minimum distance 
        int index;
        for(int j=0;j<nor;j++)
        {
            if(abs(service[ss-1]-req[j])==min)
            {
                //Make sure it is not serviced already 
                int flag=0;
                for(int k=0;k<ss;k++)
                {
                    if(service[k]==req[j])
                    {
                        flag=1;
                    }
                }
                if(flag==0)
                {
                    //Index of the request to be serviced next 
                    index=j;
                }
            }
        }
        //Add it to the service array 
        service[ss]=req[index];
        ss+=1; //Increment service array size 
    }
    //Comoute total seek time 
    for(int i=0;i<nor;i++)
    {
        //For the first request, it is distance 
        //from head to the request 
        if(i==0)
        {
            tst+=abs(service[i]-head);
        }
        //For the rest, it is distance from that request
        //to the previous request 
        else
        {
            tst+=abs(service[i]-service[i-1]);
        }
    }
    //cout<<"Total Seek time (distance):"<<endl;
    cout<<tst<<endl;
}