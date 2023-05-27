//Including Header File
#include<stdio.h>
//Initializing Ready queue 
int q[100];
int rear=-1; 
int front=-1;
//Function definition to insert
//the process in ready queue 
void insert(int x)
{
    if(front==-1)
    {
        //First element of the queue 
        front=0;
    }
    rear+=1; //Update rear to accommodate next element 
    q[rear]=x; //Insert at index 'rear'
}
//Function definition to remove
//the process from ready queue 
int delete()
{
    int n;
    n=q[front];
    front+=1; //Update 'front'
    //implying the previous index element
    //has been deleted
    return n;
}
//Main function 
int main()
{
    //Initializing variables 
    int pn[10],arr_time[10],burst_time[10],wt[10],tat[10];
    int n,quantum,p,t=0;
    int temp[10],exists[10]={0};
    float total_wt=0,total_tat=0,avg_wt,avg_tat;
    //Display statement 
    printf("Enter the number of processes : ");
    scanf("%d",&n); //User input 
    //Loop over n times to obtain 
    //details of processes 
    for(int i=0;i<n;i++)
    {
        printf("For the process P[%d]\n",i+1);
        pn[i]=i+1;
        printf("Enter the arrival time : ");
        scanf("%d",&arr_time[i]);
        printf("Enter the burst time : ");
        scanf("%d",&burst_time[i]);
        temp[i]=burst_time[i];
    }
    printf("Enter the time slice : ");
    scanf("%d",&quantum); //User input 
    //Insert the first process
    //into the queue 
    insert(0);
    exists[0]=1;
    //Loop over till the queue becomes empty 
    while(front<=rear)
    {
        p=delete();
        if(burst_time[p]>=quantum)
        {
            burst_time[p]-=quantum;
            t+=quantum;
        }
        else
        {
            t+=burst_time[p];
            burst_time[p]=0;
        }
        //If the process doesn't exist in the queue
        //then append it in the queue 
        for(int i=0;i<n;i++)
        {
            if(exists[i]==0 && arr_time[i]<=t)
            {
                insert(i); //insert into queue
                exists[i]=1; //Update exist implying 
                //it is present in the queue 
            }
        }
        //If process executes completely 
        if(burst_time[p]==0)
        {
            tat[p]=t-arr_time[p];
            wt[p]=tat[p]-temp[p];
            total_tat+=tat[p];
            total_wt+=wt[p];
        }
        else
        {
            insert(p);
        }
    }
    //Computing Average TurnAround Time
    avg_tat=total_tat/n;
    //Computing Average Waiting Time 
    avg_wt=total_wt/n;
    printf("\n");
    //Displaying output 
    printf("Process WaitingTime TurnAroundTime\n");
    for(int i=0;i<n;i++)
    {
        printf("%d \t%d \t\t%d\n",pn[i],wt[i],tat[i]);
    }
    printf("\n");
    printf("Average Waiting Time is : %.2f\n",avg_wt);
    printf("Average Turnaround Time : %.2f\n",avg_tat);
}