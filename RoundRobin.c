#include <stdio.h>

int main() {
    int bt[20], wt[20], tat[20], ct[20], rem_bt[20];
    int i, j, n, time_slice, time = 0, processes_left;
    float wtavg = 0, tatavg = 0;

    printf("\nEnter the Number of Processes: ");
    scanf("%d", &n);

    // Input burst times
    for (i = 0; i < n; i++) {
        printf("Enter Burst time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i]; // Initialize remaining burst time for each process
    }

    printf("Enter the Time Slice: ");
    scanf("%d", &time_slice);

    processes_left = n; // Number of processes left to complete

    // Round Robin Scheduling
    while (processes_left > 0) {
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0) { // Process has remaining burst time
                if (rem_bt[i] <= time_slice) {
                    time += rem_bt[i];
                    tat[i] = time; // Turnaround time for this process
                    rem_bt[i] = 0; // Process completed
                    processes_left--; // Decrement process count
                } else {
                    time += time_slice;
                    rem_bt[i] -= time_slice;
                }
            }
        }
    }

    // Calculate waiting time and averages
    for (i = 0; i < n; i++) {
        tat[i] = tat[i]; // Turnaround time is already calculated in Round Robin loop
        wt[i] = tat[i] - bt[i]; // Waiting time = turnaround time - burst time
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\n\tPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("\n\tP%d\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time: %.2f", wtavg / n);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

    return 0;
}
/*
#include <stdio.h>

int main() {
    int bt[20], wt[20], tat[20], ct[20], rem_bt[20];
    int i, j, n, time_slice, time = 0, processes_left;
    float wtavg = 0, tatavg = 0;

    printf("\nEnter the Number of Processes: ");
    scanf("%d", &n);

    // Input burst times
    for (i = 0; i < n; i++) {
        printf("Enter Burst time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i]; // Initialize remaining burst time for each process
    }

    printf("Enter the Time Slice: ");
    scanf("%d", &time_slice);

    processes_left = n; // Number of processes left to complete

    // Round Robin Scheduling
    while (processes_left > 0) {
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0) { // Process has remaining burst time
                if (rem_bt[i] <= time_slice) {
                    time += rem_bt[i];
                    tat[i] = time; // Turnaround time for this process
                    rem_bt[i] = 0; // Process completed
                    processes_left--; // Decrement process count
                } else {
                    time += time_slice;
                    rem_bt[i] -= time_slice;
                }
            }
        }
    }

    // Calculate waiting time and averages
    for (i = 0; i < n; i++) {
        tat[i] = tat[i]; // Turnaround time is already calculated in Round Robin loop
        wt[i] = tat[i] - bt[i]; // Waiting time = turnaround time - burst time
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\n\tPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("\n\tP%d\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time: %.2f", wtavg / n);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

    return 0;
}
*/
