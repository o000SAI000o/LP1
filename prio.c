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

The code you provided implements the **Priority Scheduling** algorithm for process scheduling. This algorithm schedules processes based on their priority, where lower priority numbers indicate higher priority. The key features of this algorithm are:

1. **Priority Scheduling:**
   - Each process is assigned a priority.
   - The process with the highest priority (lowest priority number) is scheduled first.

2. **Burst Time** is the time required by a process for execution, and **Turnaround Time (TAT)** is the total time a process spends in the system (waiting + execution time). **Waiting Time (WT)** is the time a process spends waiting in the ready queue.

### **Code Walkthrough:**

1. **Input:**
   - The program first asks for the number of processes (`n`).
   - For each process, the **burst time** and **priority** are input. The process IDs are assigned as `p[i]`.

2. **Sorting by Priority:**
   - The processes are sorted in increasing order of priority (i.e., the process with the lowest priority number gets scheduled first). This is done using a simple bubble sort algorithm.

3. **Waiting Time Calculation:**
   - The waiting time for the first process is `0` since it doesn't have to wait.
   - For subsequent processes, the waiting time is the sum of the burst times of all the previous processes. 
   - This is calculated using the formula:
     ```
     wt[i] = wt[i - 1] + bt[i - 1]
     ```

4. **Turnaround Time Calculation:**
   - The turnaround time is the sum of the waiting time and burst time for each process:
     ```
     tat[i] = wt[i] + bt[i]
     ```

5. **Average Calculation:**
   - The program calculates the **average waiting time** and **average turnaround time** by summing the respective times for all processes and dividing by the number of processes (`n`).

6. **Output:**
   - The program prints the process number, priority, burst time, waiting time, and turnaround time for each process.
   - Finally, it displays the average waiting time and average turnaround time.

### **Example Walkthrough:**

**Input:**
```
Enter number of processes: 4
Enter Burst Time and Priority for Process 1: 5 3
Enter Burst Time and Priority for Process 2: 2 4
Enter Burst Time and Priority for Process 3: 6 1
Enter Burst Time and Priority for Process 4: 4 2
```

**Sorted Process Table (by Priority):**
| Process | Priority | Burst Time |
|---------|----------|------------|
| P3      | 1        | 6          |
| P4      | 2        | 4          |
| P1      | 3        | 5          |
| P2      | 4        | 2          |

**Calculations:**
- **Waiting Time (WT)**:
  - For **P3**: `WT[0] = 0` (since it's the first process).
  - For **P4**: `WT[1] = WT[0] + BT[0] = 0 + 6 = 6`.
  - For **P1**: `WT[2] = WT[1] + BT[1] = 6 + 4 = 10`.
  - For **P2**: `WT[3] = WT[2] + BT[2] = 10 + 5 = 15`.

- **Turnaround Time (TAT)**:
  - For **P3**: `TAT[0] = WT[0] + BT[0] = 0 + 6 = 6`.
  - For **P4**: `TAT[1] = WT[1] + BT[1] = 6 + 4 = 10`.
  - For **P1**: `TAT[2] = WT[2] + BT[2] = 10 + 5 = 15`.
  - For **P2**: `TAT[3] = WT[3] + BT[3] = 15 + 2 = 17`.

**Output:**
```
Process   Priority   Burst   Waiting   Turnaround
P3        1          6       0         6
P4        2          4       6         10
P1        3          5       10        15
P2        4          2       15        17

Average Waiting Time: 7.75
Average Turnaround Time: 12.00
```

### **Explanation of Output:**
- **P3** is scheduled first because it has the highest priority (priority = 1).
- **P4** comes next with priority 2.
- **P1** and **P2** follow with priorities 3 and 4, respectively.
- The **average waiting time** and **average turnaround time** are calculated as:
  - Average Waiting Time = `(0 + 6 + 10 + 15) / 4 = 7.75`
  - Average Turnaround Time = `(6 + 10 + 15 + 17) / 4 = 12.00`

### **Key Takeaways:**
- The program implements **Priority Scheduling** using the **non-preemptive** approach, where the process with the highest priority (smallest priority number) is executed first.
- It calculates and displays both **waiting time** and **turnaround time** for each process.
- **Sorting** is done based on priority before calculating waiting and turnaround times.

This approach works well when priority is used to determine the order of execution. However, if priorities are dynamic or processes have equal priorities, this algorithm might need to be adapted (e.g., for tie-breaking).

*/

