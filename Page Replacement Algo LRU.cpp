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
    cout<<"Length of the reference string"<<endl;
    cin>>length; //User input 
    cout<<"Reference string"<<endl;
    for(int i=0;i<length;i++)
    {
        cin>>page[i]; //Input page string 
    }
    cout<<"Size of frame"<<endl;
    cin>>size; //User input
    //Declaring and initializing variables 
    //pif - number of pages in frame
    //frame array - to store the pages in the frame at a moment
    //faults - to store the number of page faults 
    int pif=0,frame[size],faults=0;
    //flag - to indicate the presence of a page already in the frame
    int flag;
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
                //lru array - to store the pages in the frame
                //in the order of occurence in the page reference string 
                //so as to obtain the page which occured the last in reverse
                //pilru - number of pages in lru
                //presentif - if present in frame
                //presentilru - if present in lru
                //index - to store the index of the page which occured the last in reverse
                int lru[size]={},pilru=0,presentif;
                int presentilru,index;
                //Traverse the pages in page reference string in reverse order 
                for(int k=i-1;k>=0;k--)
                {
                    //We don't know if the page is present in frame or not 
                    presentif=0;
                    //Traverse the frame 
                    for(int l=0;l<size;l++)
                    {
                        //If present in the frame 
                        if(page[k]==frame[l])
                        {
                            presentif=1; //Set flag to 1 
                        }
                    }
                    //Further computations if present in frame 
                    if(presentif==1)
                    {
                        //We don't know if the page is stored in lru array 
                        presentilru=0;
                        //Traverse the lru array 
                        for(int m=0;m<pilru;m++)
                        {
                            //If present in lru 
                            if(lru[m]==page[k])
                            {
                                presentilru=1; //Set to 1 
                            }
                        }
                        //If not present in lru 
                        if(presentilru==0)
                        { 
                            //Add it to lru array 
                            lru[pilru]=page[k];
                            //Increment the number of pages in lru 
                            pilru+=1; 
                        }
                        //Thus, we have those pages in lru 
                        //which are present in the frame 
                        //but is stored in an order 
                        //so that we can obtain the page which occured least recently 
                        //so that it can be replaced 
                    }
                    //Once, we add all the pages of frame in lru in order 
                    if(pilru==size)
                    {
                        index=k; //Store the index of the page which occured least recently 
                        break; //Stop the loop 
                    }
                }
                //We have got the index of the page which occured least recently 
                //Now find this page in the frame 
                int replace=0;
                for(int z=0;z<size;z++)
                {
                    //When found 
                    if(frame[z]==page[index])
                    {
                        replace=z; //Store the index of the page least recently used 
                    }
                }
                //Replace the page in frame 
                frame[replace]=page[i];
                faults+=1; //Increment
            }
        }
    }
    //Display output
    cout<<"Page Faults"<<endl;
    cout<<faults<<endl;
}