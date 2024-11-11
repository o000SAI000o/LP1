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

/*
This code implements the **First-Come, First-Served (FCFS)** scheduling algorithm, which is a simple and commonly used CPU scheduling algorithm. In FCFS, processes are executed in the order they arrive (i.e., the process that arrives first is executed first).

### **Explanation of the Code:**

1. **Input:**
   - The user is asked to enter the number of processes (`n`).
   - For each process, the user provides the **burst time** (the time required for the process to complete).

2. **Data Structures:**
   - `bt[20]`: An array holding the burst time of each process.
   - `wt[20]`: An array holding the waiting time for each process.
   - `tat[20]`: An array holding the turnaround time for each process.
   - `wtavg`: Variable to store the average waiting time.
   - `tatavg`: Variable to store the average turnaround time.

3. **Initialization:**
   - The **waiting time** for the first process is set to 0 (`wt[0] = 0`) because it starts execution immediately.
   - The **turnaround time** for the first process is simply its burst time (`tat[0] = bt[0]`).
   
4. **Computation:**
   - For each process (from the second one onward), the **waiting time** is calculated as the sum of the burst times of all previous processes.
   - The **turnaround time** for each process is the sum of its waiting time and burst time.
   - The averages for **waiting time** (`wtavg`) and **turnaround time** (`tatavg`) are updated by summing the individual times.

5. **Output:**
   - The program displays a table showing:
     - Process number (P1, P2, etc.).
     - Burst time for each process.
     - Waiting time for each process.
     - Turnaround time for each process.
   - The average waiting time and average turnaround time are displayed at the end.

### **Step-by-Step Example:**

Let’s walk through an example.

**Input:**
```
Enter the Number of Processes: 4
Enter Burst time for Process 1 -- 10
Enter Burst time for Process 2 -- 5
Enter Burst time for Process 3 -- 8
Enter Burst time for Process 4 -- 4
```

**Execution:**
- The program calculates the waiting time and turnaround time for each process.
- For the first process (P1), the waiting time is `0` and the turnaround time is the burst time (`10`).
- For subsequent processes:
  - The waiting time is the sum of burst times of all previous processes.
  - The turnaround time is the waiting time plus the burst time of the current process.

**Output:**
```
PROCESS       BURST TIME     WAITING TIME    TURNAROUND TIME
    P1           10            0               10
    P2            5            10              15
    P3            8            15              23
    P4            4            23              27

Average Waiting Time: 12.00
Average Turnaround Time: 13.75
```

### **Explanation of the Output:**
- **Process P1:** 
  - Waiting Time = `0`
  - Turnaround Time = `10`
  
- **Process P2:**
  - Waiting Time = `10` (since P1 took 10 units)
  - Turnaround Time = `15` (10 + 5)

- **Process P3:**
  - Waiting Time = `15` (P1 + P2 burst times)
  - Turnaround Time = `23` (15 + 8)

- **Process P4:**
  - Waiting Time = `23` (P1 + P2 + P3 burst times)
  - Turnaround Time = `27` (23 + 4)

The averages are then computed:
- Average Waiting Time = `(0 + 10 + 15 + 23) / 4 = 12.00`
- Average Turnaround Time = `(10 + 15 + 23 + 27) / 4 = 13.75`

### **Key Points:**
- **Waiting Time (WT):** The amount of time a process spends waiting in the ready queue before execution. It can be calculated as the sum of burst times of all previous processes.
- **Turnaround Time (TAT):** The total time taken from submission to completion. It is the sum of waiting time and burst time for each process.
- **Average Waiting Time:** The mean of all processes' waiting times.
- **Average Turnaround Time:** The mean of all processes' turnaround times.

### **Edge Cases:**
- If the number of processes is `1`, the waiting time will be `0` and turnaround time will be equal to the burst time of that process.
- If all processes have the same burst time, the waiting time will increase linearly, and the turnaround time will reflect this.

*/
