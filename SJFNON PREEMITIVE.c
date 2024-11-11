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
/*
The code provided implements the **Shortest Job First (SJF)** scheduling algorithm, a type of **non-preemptive scheduling**. The SJF algorithm prioritizes the process with the shortest burst time to be executed first, leading to minimal average waiting time and turnaround time.

### **Explanation of the Code:**

1. **Input:**
   - The user is prompted to input the number of processes (`n`).
   - The burst time for each process is then entered by the user.

2. **Process Sorting (SJF Algorithm):**
   - The processes are sorted by their burst time using a **Bubble Sort**. This ensures that the process with the shortest burst time gets executed first.

3. **Waiting Time Calculation:**
   - The waiting time for the first process is `0` because it doesn't have to wait for any other process.
   - For each subsequent process, the waiting time is calculated as the sum of the burst times of all previous processes.
   - The average waiting time is accumulated in `wtavg`.

4. **Turnaround Time Calculation:**
   - The turnaround time for each process is calculated as the sum of its burst time and its waiting time.
   - The average turnaround time is accumulated in `tatavg`.

5. **Displaying the Results:**
   - The process ID, burst time, waiting time, and turnaround time are displayed for each process.
   - The average waiting time and average turnaround time are also displayed.

### **Key Concepts:**
- **Burst Time**: The time required by each process for its execution.
- **Waiting Time (WT)**: The total time a process has to wait in the ready queue before it gets executed. It is calculated as the sum of the burst times of all processes that arrived before the current process.
- **Turnaround Time (TAT)**: The total time taken from the arrival of the process to its completion. It is the sum of the waiting time and the burst time for the process.
- **Shortest Job First (SJF)**: This algorithm schedules the process with the smallest burst time next. It works well when processes' burst times are known in advance.

### **Step-by-Step Example:**

Assume the following input:
```
Enter the Number of Processes: 3
Enter Burst time for each Process:
P1 : 6
P2 : 8
P3 : 7
```

1. **Sort Processes by Burst Time:**
   - Process IDs: `P1`, `P2`, `P3`
   - Burst Times: `6, 8, 7`
   - After sorting: `P1` (6), `P3` (7), `P2` (8)

2. **Waiting Time Calculation:**
   - For `P1`, waiting time is `0`.
   - For `P3`, waiting time is the burst time of `P1` (6).
   - For `P2`, waiting time is the burst times of `P1` + `P3` (6 + 7 = 13).

3. **Turnaround Time Calculation:**
   - For `P1`, turnaround time is `6` (burst time + waiting time).
   - For `P3`, turnaround time is `7 + 6 = 13`.
   - For `P2`, turnaround time is `8 + 13 = 21`.

4. **Display Results:**

```
    PROCESS    BURST TIME    WAITING TIME    TURNAROUND TIME
    P1         6             0               6
    P3         7             6               13
    P2         8             13              21

Average Waiting Time: 6.33
Average Turnaround Time: 13.33
```

### **Time Complexity:**
- **Sorting Step (Bubble Sort)**: O(n²), where `n` is the number of processes. This is the most computationally expensive part of the algorithm.
- **Waiting and Turnaround Time Calculation**: O(n), where `n` is the number of processes.

### **Edge Cases:**
- **All processes have the same burst time**: In this case, the order of execution doesn’t matter, as all processes are effectively treated equally.
- **Single process**: The process will have a waiting time of `0` and turnaround time equal to its burst time.
- **Very large burst times**: The algorithm will still work efficiently as long as the burst times are correctly input.

### **Conclusion:**
The code correctly implements the SJF scheduling algorithm and provides an efficient way to calculate average waiting time and average turnaround time for processes based on their burst times.
*/
