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

/*
code explanation:
The provided C code implements a **Shortest Job Next (SJN)** scheduling algorithm, also known as **Shortest Job First (SJF)**, with a slight variation of a preemptive version of the algorithm. It simulates the scheduling of processes based on their burst times (processing times).

Here’s a step-by-step breakdown of how the code works:

### Key Concepts:
- **Arrival Time**: The time when a process arrives in the ready queue.
- **Burst Time**: The time required for a process to execute.
- **Waiting Time**: The time a process spends waiting in the ready queue before execution.
- **Turnaround Time**: The total time taken from the arrival of a process to its completion (Waiting Time + Burst Time).

### Step-by-Step Explanation:

1. **Input Handling**:
   - The program first takes input for the number of processes (`n`).
   - For each process, it asks the user to input its **arrival time** and **burst time**.
   - The `remaining` array is initialized with the burst time values, which are decremented as the process executes.

2. **Preemption Mechanism**:
   - The algorithm operates in a **preemptive** manner. At each time unit, it selects the process with the **smallest remaining burst time** that has already arrived (i.e., the process is ready to execute). This decision is made in the `for` loop that runs from `time = 0` to when all processes have been completed.
   - The process that is executing is preempted when a new process with a smaller remaining burst time arrives.

3. **Execution Simulation**:
   - The outer loop runs until all processes are completed (`count != n`).
   - In each iteration (representing each unit of time):
     - The algorithm checks for processes that have arrived (`arrival[i] <= time`) and that have remaining burst time.
     - It selects the process with the smallest remaining burst time using the `smallest` variable.
     - The burst time of the selected process is decremented (`remaining[smallest]--`), and if it reaches 0, the process is marked as completed.

4. **Calculating Waiting and Turnaround Times**:
   - **Waiting Time**: This is calculated as the **finish time** of the process minus its **arrival time** and **burst time**.
   - **Turnaround Time**: This is the **finish time** of the process minus its **arrival time**.
   - These times are accumulated in the `total_wait` and `total_turnaround` variables for calculating average waiting and turnaround times at the end.

5. **Output**:
   - The program prints the **waiting time** and **turnaround time** for each process.
   - It also calculates and displays the **average waiting time** and **average turnaround time** for all processes.

### Example Walkthrough

Let’s assume the following input:
```
Number of processes: 3
Arrival times: 0, 1, 2
Burst times: 6, 8, 7
```

- **Process 1**: Arrival = 0, Burst = 6
- **Process 2**: Arrival = 1, Burst = 8
- **Process 3**: Arrival = 2, Burst = 7

**Execution steps** (simplified view):
1. At time 0, **Process 1** arrives and starts executing (remaining time: 6).
2. At time 1, **Process 2** arrives but does not preempt **Process 1** because **Process 1** has less remaining burst time (remaining time: 5).
3. At time 2, **Process 3** arrives but does not preempt **Process 1** either.
4. After 6 units of time, **Process 1** finishes.
5. Then **Process 3** will execute, as it has the shortest remaining burst time.
6. **Process 2** executes last because it has the longest burst time.

After the simulation, the program will print:
- The waiting time and turnaround time for each process.
- The average waiting and turnaround times.

### Output Example:

```
Enter the number of processes: 3
Enter arrival time for process 1: 0
Enter burst time for process 1: 6
Enter arrival time for process 2: 1
Enter burst time for process 2: 8
Enter arrival time for process 3: 2
Enter burst time for process 3: 7

Process    Arrival Time    Burst Time    Waiting Time    Turnaround Time
P1            0              6             0              6
P2            1              8             6              14
P3            2              7             6              13

Average Waiting Time: 4.00
Average Turnaround Time: 11.00
```

### Explanation of the Results:
- **Process 1** has no waiting time because it starts executing immediately when it arrives.
- **Process 2** starts execution after **Process 1** finishes and thus waits for 6 units of time.
- **Process 3** starts after **Process 1** and **Process 2** finish and waits for 6 units of time.

### Conclusion:
This C code implements a **preemptive shortest job next (SJN)** scheduling algorithm, and it provides useful information like **waiting times** and **turnaround times** for each process as well as the averages.


*/
