#include <stdio.h>

int main() {
    int bt[20], wt[20], tat[20], i, n;
    float wtavg, tatavg;

    printf("\n Enter the Number of Processes : ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter Burst time for Process %d -- ", (i + 1));
        scanf("%d", &bt[i]);
    }

    wt[0] = wtavg = 0; // First process has no waiting time
    tat[0] = tatavg = bt[0]; // Turnaround time for the first process is its burst time

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1]; // Waiting time for current process
        tat[i] = wt[i] + bt[i]; // Turnaround time is waiting time + burst time
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\n\tPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("\n\tP%d\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time : %.2f", wtavg / n);
    printf("\nAverage Turnaround Time : %.2f\n", tatavg / n);

    printf("\nPress any key to exit...");
    getchar(); // Consume newline left by last scanf
    getchar(); // Wait for user input
    return 0;
}

