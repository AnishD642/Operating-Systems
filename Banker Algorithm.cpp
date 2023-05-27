//Including Header Files
#include<iostream>
using namespace std;
//Function definition for safety algorithm
//Passing the number of proesses, resources 
//allocation array, need array and available array
bool safety(int n, int m, int allocation[100][100], int need[100][100], int available[100])
{
    //Initializing variables
    int work[m],seq[n],index=0;
    bool finish[n];
    bool flag=false;
    //Traverse the list and
    //copy available in work 
    //work=available
    for(int i=0;i<m;i++)
    {
        work[i]=available[i];
    }
    //Traverse the list and 
    //initialize all finish to false 
    for(int i=0;i<n;i++)
    {
        finish[i]=false;
    }
    //The count of number of times we traverse all the processes 
    int count=0;
    //while loop condition 
    while(flag==false and count<=n)
    {
        //Traverse the processes 
        for(int i=0;i<n;i++)
        {
            //test variable to test for the 
            //condition : need < work 
            int test=0;
            //If process didn't execute earlier  
            if(finish[i]==false)
            {
                //Traverse each resource type
                for(int j=0;j<m;j++)
                {
                    //Check the condition 
                    if(need[i][j]>work[j])
                    {
                        //If condition fails 
                        //update test to 1
                        //Implying that it can't be executed
                        test=1;
                    }
                }
                //If condition satisfies 
                if(test==0)
                {
                    //Traverse each resource type 
                    for(int j=0;j<m;j++)
                    {
                        //Update work to work + allocation 
                        work[j]=work[j]+allocation[i][j];
                    }
                    //Finish is updated to true 
                    finish[i]=true;
                    //This process is appended to the list of safe sequence 
                    seq[index]=i;
                    //index of next input of safe sequence updated 
                    index+=1;
                }
            }
        }
        //temp variable is used to check how many processes have executed 
        int temp=0;
        for(int i=0;i<n;i++)
        {
            if(finish[i]==true)
            {
                //Increase temp by 1 after every process completes 
                temp+=1;
            }
        }
        //If temp = number of processes 
        //implies all processes have completed execution 
        if(temp==n)
        {
            //Update flag to true implying all executed 
            flag=true;
        }
        else
        {
            //else flag is false implying not all processes executed 
            flag=false;
        }
        //count variable is updated by 1 
        //since by this time we have traversed through 
        //all the processes once again  
        count+=1;
    }
    //If all processes executed 
    if(flag==true)
    {
        //Implies system is in safe state and there is a safe sequence 
        cout<<"The system is in SAFE state"<<endl;
        cout<<"The safe sequence is : "<<endl;
        for(int i=0;i<n;i++)
        {
            //Display safe sequence 
            cout<<seq[i]<<" ";
        }
        cout<<"\n";
        return true; //returns true when in safe state 
    }
    else
    {
        cout<<"The system is in UNSAFE state"<<endl;
        return false; //returns false when in unsafe state 
    }
}
//Function definition for resource request algorithm 
//Passing number of processes, resources
//allocation, need and available arrays to the function 
void resource_request(int n, int m, int allocation[100][100], int max[100][100], int need[100][100], int available[100])
{
    //Initializing variables
    int request[m],rp,flag=0;
    bool result;
    cout<<"Enter the process number by which request is made : "<<endl;
    cin>>rp; //User input 
    cout<<"Enter the number of instances of each resource type to be requested : "<<endl;
    for(int i=0;i<m;i++)
    {
        cin>>request[i]; //User input 
    }
    for(int i=0;i<n;i++)
    {
        if(i==rp) //For the process requesting resources 
        {
            //Traverse through the resource types 
            for(int j=0;j<m;j++)
            {
                //If request is more then need or available 
                if(request[j]>need[i][j] and request[j]>available[j])
                {
                    //Set flag to 1
                    //Implying request cannot be granted since it is more then need/available 
                    flag=1;
                }
            }
        }
    }
    //If request is less than need and available 
    if(flag==0)
    {
        for(int i=0;i<n;i++)
        {
            if(i==rp) //For the process requesting resources 
            {
                //Traverse through the resource types 
                for(int j=0;j<m;j++)
                {
                    //Apply formulae of Resource request algorithms 
                    available[j]=available[j]-request[j];
                    allocation[i][j]=allocation[i][j]+request[j];
                    need[i][j]=need[i][j]-request[j];
                }
            }
        }
        //Call safety algorithm to check for safety if request granted 
        result=safety(n,m,allocation,need,available);
        //If system is in safe state if the request is granted 
        //result is true
        if(result==true)
        {
            //Display output 
            cout<<"The state of the system will be safe"<<endl;
            cout<<"Request can be granted -- No deadlock"<<endl;
            cout<<"The updated table is : "<<endl;
            cout<<"Process \tAllocation  \tMax  \t\tNeed"<<endl;
            //Display updated table values 
            for(int i=0;i<n;i++)
            {
                cout<<"P["<<i<<"]     \t";
                for(int j=0;j<m;j++)
                {
                    cout<<allocation[i][j]<<" ";
                }
                cout<<"   \t";
                for(int j=0;j<m;j++)
                {
                    cout<<max[i][j]<<" ";
                }
                cout<<"   \t";
                for(int j=0;j<m;j++)
                {
                    cout<<need[i][j]<<" ";
                }
                cout<<"\n";
            }
            cout<<"Available instances of resource types are : "<<endl;
            for(int i=0;i<m;i++)
            {
                cout<<available[i]<<" ";
            }
            cout<<"\n";
        }
        //If system is in unsafe state if the request is granted 
        //result is false
        else
        {
            cout<<"The state of the system will become unsafe"<<endl;
            cout<<"Request cannot be granted"<<endl;
        }
    }
    //Request cannot be granted since it is more than need or available 
    else
    {
        cout<<"Request cannot be granted"<<endl;
        cout<<"The resources requested is more than need/available"<<endl;
    }
}
int main() //Main function 
{
    //Initializing variables 
    int m,n;
    int allocation[100][100], max[100][100], need[100][100];
    int available[100];
    char ch;
    bool x;
    cout<<"Enter the number of processes : "<<endl;
    cin>>n; //User input 
    cout<<"Enter the number of resources : "<<endl;
    cin>>m; //User input 
    cout<<"Enter the details of each process : "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"For process P["<<i<<"] : "<<endl;
        cout<<"Enter Allocation details of each resource type : "<<endl;
        for(int j=0;j<m;j++)
        {
            cin>>allocation[i][j];
        }
        cout<<"Enter Max details of each resource type : "<<endl;
        for(int k=0;k<m;k++)
        {
            cin>>max[i][k];
        }
        //To compute need array
        //need = max - allocation 
        for(int l=0;l<m;l++)
        {
            need[i][l]=max[i][l]-allocation[i][l];
        }
        //Display statement 
        cout<<"The need of the process for every resource type has been computed"<<endl;
        cout<<"--------------------"<<endl;
    }
    //User input available resource instances 
    cout<<"Enter the available instances of each resource type : "<<endl;
    for(int i=0;i<m;i++)
    {
        cin>>available[i];
    }
    //Display input in tabular form 
    cout<<"The input is : "<<endl;
    cout<<"Process \tAllocation  \tMax  \t\tNeed"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P["<<i<<"]     \t";
        for(int j=0;j<m;j++)
        {
            cout<<allocation[i][j]<<" ";
        }
        cout<<"   \t";
        for(int j=0;j<m;j++)
        {
            cout<<max[i][j]<<" ";
        }
        cout<<"   \t";
        for(int j=0;j<m;j++)
        {
            cout<<need[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"Available instances of resource types are : "<<endl;
    for(int i=0;i<m;i++)
    {
        cout<<available[i]<<" ";
    }
    cout<<"\n";
    cout<<"\n";
    //Function call for safety algorithm 
    //To check if the system is in safe state or not 
    x=safety(n,m,allocation,need,available);
    cout<<"\n";
    //If the system is in a safe state 
    if(x==true)
    {
        //Resource request user input
        cout<<"Does any process wants to request resources? Y or N : "<<endl;
        cin>>ch;
        //If any process wants to request resources 
        if(ch=='Y')
        {
            //Function call for request resource algorithm
            //Checks if the request grant leads to safe state or unsafe state 
            resource_request(n,m,allocation,max,need,available);
        }
    }
}