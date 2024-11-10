#include <stdio.h>

int main() {
    int n, i, smallest, time, count = 0;
    int arrival[10], burst[10], remaining[10], finish_time[10];
    float total_wait = 0, total_turnaround = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
    }

    remaining[9] = 9999; // Large value to act as sentinel for process selection
    for (time = 0; count != n; time++) {
        smallest = 9;
        
        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] < remaining[smallest] && remaining[i] > 0) {
                smallest = i;
            }
        }
        
        remaining[smallest]--;

        if (remaining[smallest] == 0) {
            count++;
            finish_time[smallest] = time + 1;
            total_wait += finish_time[smallest] - arrival[smallest] - burst[smallest];
            total_turnaround += finish_time[smallest] - arrival[smallest];
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        int waiting_time = finish_time[i] - arrival[i] - burst[i];
        int turnaround_time = finish_time[i] - arrival[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], waiting_time, turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}
