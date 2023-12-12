//Implement FCFS scheduling algorithm.
#include <stdio.h>

struct process
{
    int pid;
    int burst_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
};
void FirstInFirstOut(struct process processes[], int n)
{
    int time = 0;
    int completed = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0)
            {
                time += processes[i].remaining_time;
                processes[i].remaining_time = 0;
                processes[i].completion_time = time;
                processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                total_waiting_time += processes[i].waiting_time;
                total_turnaround_time += processes[i].turnaround_time;
                completed++;
            }
        }
    }
    printf("PID\tBT\tAT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("Average waiting time: %f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %f\n", (float)total_turnaround_time / n);
}







int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process processes[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time, and arrival time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].arrival_time);
        processes[i].pid = i + 1;
        processes[i].completion_time=0;
        processes[i].waiting_time=0;
        processes[i].turnaround_time=0;
        processes[i].remaining_time=processes[i].burst_time;

        
    }

    FirstInFirstOut(processes, n);
    return 0;
}