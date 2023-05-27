#include<stdio.h>
#include<string.h>
int main() //Main function 
{
    //Initializing variables
    int pn[10],t;
    int arr_time[10],burst_time[10],start[10],completion[10],wt[10],tat[10];
    int i,j,n,temp;
    int total_wt=0,total_tat=0;
    float avg_wt=0.0,avg_tat=0.0;
    //Display statement
    printf("Enter the number of processes : ");
    scanf("%d",&n);//Input from user
    printf("\nEnter each process details : \n");
    for(i=0;i<n;i++) //Iterate to input from user 
    {
        printf("Enter process name : ");
        scanf("%d",&pn[i]); //Input process number
        printf("Enter the arrival time : ");
        scanf("%d",&arr_time[i]); //Input arrival time 
        printf("Enter the burst time : ");
        scanf("%d",&burst_time[i]); //Input cpu burst time 
    }
    //Traverse through the processes list 
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            //Whichever process arrives first
            //Is scheduled first 
            if(arr_time[i]<arr_time[j])
            {
                temp=arr_time[i];
                arr_time[i]=arr_time[j];
                arr_time[j]=temp;
                temp=burst_time[i];
                burst_time[i]=burst_time[j];
                burst_time[j]=temp;
                t=pn[i];
                pn[i]=pn[j];
                pn[j]=t;
            }
        }
    }
    //Display Gantt Chart : The order of execution 
    printf("\nGantt Chart : \n");
    for(i=0;i<n;i++)
    {
        printf("P[%d] <--> ",pn[i]);
    }
    //Traverse through the scheduled list of processes 
    for(i=0;i<n;i++)
    {
        if(i==0) //First process 
        {
            //Compute start time 
            start[i]=arr_time[i];
            //Compute completion time 
            completion[i]=start[i]+burst_time[i];
            //Compute turnaround time 
            tat[i]=completion[i]-arr_time[i];
            //Compute waiting time 
            wt[i]=tat[i]-burst_time[i];
        }
        else //Consequent processes 
        {
            //Compute start time
            start[i]=completion[i-1];
            //Compute completion time
            completion[i]=start[i]+burst_time[i];
            //Compute turnaround time
            tat[i]=completion[i]-arr_time[i];
            //Compute waiting time
            wt[i]=tat[i]-burst_time[i];
        }
    }
    //Display the tabular form containing the scheduling information 
    printf("\nProcesses Arrival_Time Burst_Time Completion_Time Turn-Around_Time Waiting_Time");
    //Traverse through scheduled list 
    for(i=0;i<n;i++)
    {
        //Display the output 
        printf("\nP[%d] \t\t%d \t%d \t\t%d \t\t%d \t\t%d",pn[i],arr_time[i],burst_time[i],completion[i],tat[i],wt[i]);
        total_wt+=wt[i];
        total_tat+=tat[i];
    }
    //Computing average waiting time and average turnaround time 
    avg_wt=((float)total_wt)/n;
    avg_tat=((float)total_tat)/n;
    printf("\nAverage waiting time : %.3f",avg_wt);
    printf("\nAverage Turn Around time : %.3f\n",avg_tat);
}