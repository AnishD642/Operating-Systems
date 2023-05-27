#include<stdio.h>
#include<string.h>
int main()//Main function 
{
    //Initializing variables 
    int pn[10],t;
    int arr_time[10],burst_time[10],start[10],completion[10],wt[10],tat[10],temp_2[10];
    int n,i,j,temp,count=0,smallest,comp;
    int total_wt=0,total_tat=0,wait_time=0,turnAroundTime=0;
    float avg_wt=0.0,avg_tat=0.0;
    //Display statement 
    printf("Enter the number of processess : ");
    scanf("%d",&n);//Input number of processes 
    printf("\nEnter the details : \n");
    //Iterative input from user 
    for(i=0;i<n;i++)
    {
        printf("Enter Process Name: ");
        scanf("%d",&pn[i]);//Input process number 
        printf("Enter the arrival time: ");
        scanf("%d",&arr_time[i]);//Input arrival time 
        printf("Enter the burst time: ");
        scanf("%d",&burst_time[i]);//Input cpu burst time 
        temp_2[i]=burst_time[i];//temporary list 
    }
    burst_time[9]=9999;
    //Pre-emptive sjf scheduling 
    for(i=0;count!=n;i++)
    {
        smallest=9;
        for(j=0;j<n;j++)
        {
            if(arr_time[j]<=i && burst_time[j]<burst_time[smallest] && burst_time[j]>0)
            {
                smallest=j;
            }
        }
        burst_time[smallest]--;//Decrement burst time after partial execution 
        if(burst_time[smallest]==0)
        {
            //Process name 
            printf("Process %d\n",pn[smallest]);
            count++;
            comp=i+1;
            //Computing completion time 
            completion[smallest]=comp;
            //Computing waiting time 
            wt[smallest]=comp-arr_time[smallest]-temp_2[smallest];
            //Computing turnaround time 
            tat[smallest]=comp-arr_time[smallest];
            //Displaying completion time 
            printf("Completion time of process %d is %d\n",pn[smallest],comp);
            wait_time=wait_time+comp-arr_time[smallest]-temp_2[smallest];
            turnAroundTime=turnAroundTime+comp-arr_time[smallest];
        }
    }
    //Displaying tabular form 
    printf("\nProcesses Arrival_Time Burst_Time Completion_Time Turn-Around_Time Waiting_Time");
    //Iterate through the processes 
    for (i=0;i<n;i++)
    {
        //Displaying output 
        printf("\nP[%d] \t\t%d \t%d \t\t%d \t\t%d \t\t%d",pn[i],arr_time[i],temp_2[i],completion[i],tat[i],wt[i]);
    }
    //Computing average waiting time and turnaround time 
    avg_wt=((float)wait_time)/n;
    avg_tat=((float)turnAroundTime)/n;
    printf("\nAverage waiting time: %.3f",avg_wt);
    printf("\nAverage Turn Around time: %.3f\n",avg_tat);
}