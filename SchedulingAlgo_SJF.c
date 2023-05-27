#include<stdio.h>
#include<string.h>
int main()//Main function 
{
    //Initializing variables 
    int pn[10],t;
    int arr_time[10],burst_time[10],start[10],completion[10],wt[10],tat[10];
    int n,i,j,temp,flag=0;
    int total_wt=0,total_tat=0;
    //Display statement 
    printf("Enter the number of processess : ");
    scanf("%d",&n);//Input from user 
    printf("\nEnter each process detail : \n");
    //Iterate to input from user 
    for(i=0;i<n;i++)
    {
        printf("Enter Process Name: ");
        scanf("%d",&pn[i]);//Input process number
        printf("Enter the arrival time: ");
        scanf("%d",&arr_time[i]);//Input arrival time 
        printf("Enter the burst time: ");
        scanf("%d",&burst_time[i]);//Input cpu burst time 
    }
    //Arrange according to arrival time 
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
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
    //If the starting process does not have arrival_time=0 
    for(i=0;i<n;i++)
    {
        if(arr_time[i]!=0)
        {
            flag=1;//Flag
            break;
        }
    }
    //If arrival time is not zero 
    if(flag==1)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                //Arrange according to burst time 
                //Minimum burst time given first chance 
                if(burst_time[i]<burst_time[j])
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
    }
    //If arrival time is zero 
    else
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                //Arrange according to burst time 
                //Minimum burst time given first chance
                if(burst_time[i]<burst_time[j])
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
    }
    //Traverse through the list of processes 
    //Compute the metrics for each process 
    for(i=0;i<n;i++)
    {
        if(i==0)//Starting process 
        {
            start[i]=arr_time[i];
        }
        else//Consequent processes 
        {
            start[i]=completion[i-1];
        }
        //Compute waiting time 
        wt[i]=start[i]-arr_time[i];
        //Compute completion time 
        completion[i]=start[i]+burst_time[i];
        //Compute turnaround time 
        tat[i]=completion[i]-arr_time[i];
    }
    //Display tabular form 
    printf("\nProcesses Arrival_Time Burst_Time Completion_Time Turn-Around_Time Waiting_Time");
    //Traverse through the processes in order 
    for (i=0;i<n;i++)
    {
        //Display output 
        printf("\nP[%d] \t\t%d \t%d \t\t%d \t\t%d \t\t%d",pn[i],arr_time[i],burst_time[i],completion[i],tat[i],wt[i]);
        total_wt+=wt[i];
        total_tat+=tat[i];
    }
    //Displaying average waiting time and turnaround time 
    printf("\nAverage waiting time: %.3f",(float)(total_wt)/n);
    printf("\nAverage Turn Around time: %.3f\n",(float)(total_tat)/n);
}