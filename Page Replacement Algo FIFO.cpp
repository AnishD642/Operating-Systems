//Including Header File 
#include<iostream>
using namespace std;
//Main function 
int main()
{
    //Declaring and initializing variables 
    //size - size of the frame
    //page array - to store the page reference string  
    //length - number of pages 
    int size,page[100],length;
    //cout<<"Length of the reference string"<<endl;
    cin>>length; //User input 
    //cout<<"Reference string"<<endl;
    for(int i=0;i<length;i++)
    {
        cin>>page[i]; //Input page string 
    }
    //cout<<"Size of frame"<<endl;
    cin>>size; //User input 
    //Declaring and initializing variables 
    //pif - number of pages in frame
    //frame array - to store the pages in the frame at a moment
    //faults - to store the number of page faults  
    int pif=0,frame[size],faults=0;
    //flag - to indicate the presence of a page already in the frame
    //z - number of pages replaced 
    //replace - index of page to be replaced  
    int flag,z=0,replace;
    //Traverse the list of page reference string 
    for(int i=0;i<length;i++)
    {
        flag=0; //We don't know if page present in frame or not  
        //If the pages in frame are less than the maximum capacity 
        if(pif<size)
        {
            //Traverse over the pages in frame 
            for(int j=0;j<pif;j++)
            { 
                //If page already present 
                if(frame[j]==page[i])
                {
                    flag=1; //Set flag to 1 
                }
            }
            //If page not present 
            if(flag==0)
            {
                //Enter the page in the frame 
                frame[pif]=page[i];
                faults+=1; //Increment
            }
            pif+=1; //One page added to frame
        }
        //If the frame is full 
        else
        {
            //Traverse over the frame 
            for(int j=0;j<size;j++)
            {
                //If page present 
                if(frame[j]==page[i])
                {
                    flag=1; //Set to 1
                }
            }
            //If page not present 
            if(flag==0)
            { 
                //Find the page index to be replaced 
                replace=z%size;
                //Replace the page 
                frame[replace]=page[i]; 
                faults+=1; //Increment
                //Increment the number of pages replaced
                z+=1;  
            }
        }
    }
    //Display output 
    //cout<<"Page Faults"<<endl;
    cout<<faults<<endl;
}