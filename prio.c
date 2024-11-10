#include <stdio.h>

int main() {
    int n, p[20], bt[20], pr[20], wt[20] = {0}, tat[20];
    float wtavg = 0, tatavg = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst time and priority
    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d %d", &bt[i], &pr[i]);
        p[i] = i + 1;
    }

    // Sort by priority (lower number = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pr[i] > pr[j]) {
                int temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    for (int i = 1; i < n; i++) wt[i] = wt[i - 1] + bt[i - 1];
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Display results
    printf("\nProcess\tPriority\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t\t%d\t%d\t%d\n", p[i], pr[i], bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time: %.2f", wtavg / n);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

    return 0;
}


/*Enter number of processes: 4
Enter Burst Time and Priority for Process 1: 5 3
Enter Burst Time and Priority for Process 2: 2 4
Enter Burst Time and Priority for Process 3: 6 1
Enter Burst Time and Priority for Process 4: 4 2

Process	Priority	Burst	Waiting	Turnaround
P3	1		6	0	6
P4	2		4	6	10
P1	3		5	10	15
P2	4		2	15	17

Average Waiting Time: 7.75
Average Turnaround Time: 12.00
*/

