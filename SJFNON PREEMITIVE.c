#include <stdio.h>

int main() {
    int p[20], bt[20], wt[20], tat[20], i, j, temp, n;
    float wtavg = 0, tatavg = 0;

    printf("\n Enter the Number of Processes : ");
    scanf("%d", &n);

    printf("\nEnter Burst time for each Process:\n");
    for (i = 0; i < n; i++) {
        p[i] = i + 1; // Process IDs
        printf("P%d : ", p[i]);
        scanf("%d", &bt[i]);
    }

    // Sort processes by Burst Time using Bubble Sort for SJF
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                // Swap burst times
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap process IDs to match burst time order
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate Waiting Time for each process
    wt[0] = 0; // First process has no waiting time
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        wtavg += wt[i];
    }

    // Calculate Turnaround Time for each process
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        tatavg += tat[i];
    }

    // Display the results
    printf("\n\tPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("\n\tP%d\t\t%d\t\t%d\t\t%d", p[i], bt[i], wt[i], tat[i]);
    }

    // Calculate and display averages
    printf("\n\nAverage Waiting Time : %.2f", wtavg / n);
    printf("\nAverage Turnaround Time : %.2f\n", tatavg / n);

    return 0;
}
