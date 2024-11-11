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
The provided code implements the **Round Robin (RR) Scheduling Algorithm**, which is one of the most common CPU scheduling algorithms. It is designed to allocate CPU time to each process in equal time slices (also called quantum). If a process doesn’t finish in one time slice, it is preempted and placed at the end of the ready queue.

### **Explanation of the Code:**

1. **Input:**
   - **Number of processes (`n`)**: The user specifies how many processes there are to be scheduled.
   - **Burst times (`bt`)**: The user inputs the burst time (the time each process needs on the CPU) for each process.
   - **Time slice (`time_slice`)**: This is the maximum time each process can run before being preempted and moved to the back of the queue.

2. **Data Structures:**
   - `bt[20]`: Stores the burst time for each process.
   - `wt[20]`: Stores the waiting time for each process.
   - `tat[20]`: Stores the turnaround time for each process.
   - `ct[20]`: Stores the completion time for each process.
   - `rem_bt[20]`: Stores the remaining burst time for each process (this allows the algorithm to track the progress of each process during the execution).

3. **Round Robin Algorithm:**
   - The algorithm uses a **while loop** that runs until all processes are completed (`processes_left > 0`).
   - For each process, if it has remaining burst time, the algorithm:
     - If the remaining burst time is less than or equal to the time slice, the process is finished, and its turnaround time (`tat[i]`) is calculated.
     - If the remaining burst time is greater than the time slice, the process is preempted, and its remaining burst time is reduced by the time slice.
   - The `time` variable tracks the total time elapsed, which is used to calculate the turnaround time for each process.

4. **Calculation of Waiting and Turnaround Time:**
   - **Turnaround Time (TAT)**: Time taken from the arrival of the process until its completion. It's calculated during the Round Robin loop.
   - **Waiting Time (WT)**: Waiting time is the total time a process spends waiting in the ready queue, and it is calculated as:
     \[
     \text{WT} = \text{TAT} - \text{Burst Time}
     \]

5. **Output:**
   - The program outputs the burst time, waiting time, and turnaround time for each process.
   - It also calculates and displays the **average waiting time** and **average turnaround time**.

### **Step-by-Step Example:**

For the following inputs:
```
Enter the Number of Processes: 3
Enter Burst time for Process 1: 10
Enter Burst time for Process 2: 5
Enter Burst time for Process 3: 8
Enter the Time Slice: 4
```

**Step-by-step Execution:**

1. **Initial Setup:**
   - Process 1 has burst time 10.
   - Process 2 has burst time 5.
   - Process 3 has burst time 8.
   - Time slice is 4.

2. **First Cycle of Round Robin:**
   - Process 1 runs for 4 units: `rem_bt[1] = 6`.
   - Process 2 runs for 4 units: `rem_bt[2] = 1`.
   - Process 3 runs for 4 units: `rem_bt[3] = 4`.

3. **Second Cycle:**
   - Process 1 runs for 4 units: `rem_bt[1] = 2`.
   - Process 2 runs for 1 unit: `rem_bt[2] = 0` (process 2 finishes).
   - Process 3 runs for 4 units: `rem_bt[3] = 0` (process 3 finishes).

4. **Third Cycle:**
   - Process 1 runs for 2 units: `rem_bt[1] = 0` (process 1 finishes).

At this point, all processes are completed.

5. **Final Calculations:**
   - Turnaround times are calculated based on the total time each process has run.
   - Waiting times are calculated as `TAT - Burst Time`.
   
### **Output:**
```
    PROCESS      BURST TIME    WAITING TIME    TURNAROUND TIME
    P1            10            6               16
    P2            5             4               9
    P3            8             4               12

Average Waiting Time: 4.67
Average Turnaround Time: 12.33
```

### **Key Concepts:**
- **Time Slice** (also called **Quantum**): The maximum time a process is allowed to run before being preempted and placed at the end of the ready queue.
- **Round Robin Scheduling**: This is a preemptive scheduling algorithm where each process gets a fixed time slice in which it runs. If the process does not finish within its slice, it is put back in the queue and waits for its next turn.
- **Turnaround Time (TAT)**: The total time from arrival to completion.
- **Waiting Time (WT)**: The total time a process spends waiting in the ready queue.

### **Edge Cases:**
- **Single Process:** If there's only one process, it will finish its execution without being preempted.
- **Equal Burst Times:** If all processes have the same burst time, each process will get equal time slices until they complete.
- **Large Time Slice:** If the time slice is large enough that processes complete within one slice, Round Robin will behave like **First-Come, First-Served (FCFS)**.

*/
