#include<stdio.h>
int main()//Main function 
{
    //Initializing variables 
    int n,temp[10],t,count=0,short_p;
    int arr_time[10],wt[10],burst_time[10],tat[10],priority[10];
    float total_wt=0.0,total_tat=0.0;
    float avg_wt=0.0,avg_tat=0.0;
    //Display statement
    printf("Enter the number of processes : ");
    scanf("%d",&n);//Input from user
    printf("\nEnter the details of each process : \n");
    //Iterative input from user 
    for(int i=0;i<n;i++)
    {
        printf("Enter the details of process P[%d] : \n",i+1);
        printf("Enter the arrival time : ");
        scanf("%d",&arr_time[i]);//Input arrival time 
        printf("Enter the burst time : ");
        scanf("%d",&burst_time[i]);//Input burst time 
        printf("Enter the priority : ");
        scanf("%d",&priority[i]);//Input priority of process 
        //Copying the burst time in
        //A temporary array for futher use
        temp[i]=burst_time[i];
    }
    // we initialize the burst time
    // of a process with maximum 
    priority[9]=10000;
    //Principle : Lesser number implies higher priority 
    for(t=0;count!=n;t++)
    {
        short_p=9;
        for(int i=0;i<n;i++)
        {
            //If lesser number implies lesser priority 
            //then priority[short_p]<priority[i]
            if(priority[short_p]>priority[i] && arr_time[i]<=t && burst_time[i]>0)
            {
                short_p=i;
            }
        }
        burst_time[short_p]=burst_time[short_p]-1;
        //If any process is completed
        if(burst_time[short_p]==0)
        {
            //One process is completed
            //So count increases by 1
            count++;
            wt[short_p]=t+1-arr_time[short_p]-temp[short_p];
            tat[short_p]=t+1-arr_time[short_p];
            //Computing total waiting time 
            total_wt=total_wt+wt[short_p];
            //Computing total turnaround time 
            total_tat=total_tat+tat[short_p];
        }
    }
    //Computing average waiting time 
    avg_wt=total_wt/n;
    //Computing average turnaround time 
    avg_tat=total_tat/n;
    //Display tabular form 
    printf("\nProcesses Turn-Around_Time  Waiting_Time");
    for(int i=0;i<n;i++)
    {
        //Display output 
        printf("\nP[%d] \t\t%d  \t\t%d",i+1,tat[i],wt[i]);
    }
    //Display average waiting time and turnaround time 
    printf("\nAverage waiting time : %.3f",avg_wt);
    printf("\nAverage turn around time : %.3f",avg_tat);
}