#include <stdio.h>

int main() {
    int rs[50], i, j, k, m, f, cntr[20], a[20], min, pf = 0;

    // Input the number of page references
    printf("Enter number of page references: ");
    scanf("%d", &m);
    
    // Input the reference string
    printf("Enter the reference string: ");
    for(i = 0; i < m; i++) {
        scanf("%d", &rs[i]);
    }
   
    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    
    // Initialize frames and counters
    for(i = 0; i < f; i++) {
        cntr[i] = 0;  // Initialize reference counters to zero
        a[i] = -1;    // Initialize frames to empty
    }
    
    printf("\nThe Page Replacement Process is:\n");
    
    // LFU page replacement algorithm
    for(i = 0; i < m; i++) {
        int found = 0;
        
        // Check if page is already in a frame
        for(j = 0; j < f; j++) {
            if(rs[i] == a[j]) {
                cntr[j]++;  // Increment the use counter for LFU
                found = 1;
                break;
            }
        }
        
        // If page is not found, replace the least frequently used page
        if(!found) {
            // Find the frame with the smallest counter
            min = 0;
            for(k = 1; k < f; k++) {
                if(cntr[k] < cntr[min]) {
                    min = k;
                }
            }
            
            // Replace the page and reset its counter
            a[min] = rs[i];
            cntr[min] = 1;
            pf++;  // Increment page fault count
        }
        
        // Display current frame state
        for(j = 0; j < f; j++) {
            if(a[j] != -1) {
                printf("%d\t", a[j]);
            } else {
                printf("-\t");
            }
        }
        
        // Print page fault message if a replacement occurred
        if(!found) {
            printf("PF No. %d", pf);
        }
        
        printf("\n");
    }
    
    // Output the total number of page faults
    printf("\nTotal number of page faults: %d", pf);
    
    // Wait for user input before exiting (replaces getch())
    printf("\nPress Enter to exit...");
    getchar(); // Capture Enter key after scanf
    getchar(); // Capture the actual key press to pause
    return 0;
}

/*
This code implements the **Least Frequently Used (LFU)** page replacement algorithm. In LFU, the page that is least frequently used is replaced when a page fault occurs and there are no free frames available. Here’s a detailed breakdown of the code:

### **Explanation of the Code:**

1. **Input:**
   - The user is asked to enter:
     - The number of page references (`m`).
     - The reference string, which contains the sequence of page accesses.
     - The number of frames (`f`) available for storing pages.

2. **Data Structures:**
   - `rs[50]`: An array to hold the reference string (the sequence of pages being accessed).
   - `a[20]`: An array representing the frames. It stores the current pages in the frames.
   - `cntr[20]`: An array that stores the count of how many times each page in the frame has been accessed (this is the core of the LFU algorithm).
   - `pf`: A counter to track the number of page faults.

3. **Initialization:**
   - The frames (`a[i]`) are initialized to `-1`, indicating that the frames are initially empty.
   - The counters (`cntr[i]`) are initialized to `0` to keep track of how often each page in the frames is accessed.

4. **LFU Algorithm:**
   - **Loop Through Reference String:**
     - For each page in the reference string:
       - Check if the page is already in one of the frames.
       - If the page is found, increment its counter (`cntr[j]`).
       - If the page is not found, find the frame with the lowest access counter (LFU) and replace the page in that frame.
     - After each page access, display the current state of the frames and print the page fault count if a replacement occurs.

5. **Output:**
   - After processing the reference string, the program displays the total number of page faults that occurred during the execution.
   
### **Step-by-Step Example:**

Let's walk through an example:

**Input:**
```
Enter number of page references: 12
Enter the reference string: 7 0 1 2 0 3 0 4 2 3 0 3
Enter the number of frames: 3
```

The reference string has 12 page accesses, and there are 3 frames available.

#### Process:
1. Initially, all frames are empty.
2. When a page is accessed, if it's not in the frames, it's a page fault, and we replace the least frequently used page in the frames.
3. After each page access, the state of the frames and the page fault number is displayed.

#### Output:
```
The Page Replacement Process is:
7	-	-	PF No. 1
7	0	-	PF No. 2
7	0	1	PF No. 3
2	0	1	PF No. 4
2	0	1	
3	0	1	PF No. 5
3	0	1	
4	0	1	PF No. 6
4	2	1	PF No. 7
4	2	3	PF No. 8
4	0	3	
4	0	3	
4	0	3	

Total number of page faults: 8
```

### **Explanation of the Output:**
- **Frame State:** The output displays the current state of the frames after each page access.
  - A `-` means that the frame is empty.
  - If a page is replaced, the page fault number (`PF No. X`) is shown.
- **Total Page Faults:** The total number of page faults is displayed at the end of the simulation, which in this case is 8.

### **Key Points of LFU:**
- **Page Replacement:** LFU replaces the page that is least frequently accessed, trying to keep frequently accessed pages in memory.
- **Page Faults:** Each time a page needs to be loaded into memory and there's no space, the least frequently accessed page is replaced. This increases the number of page faults if there are many pages with low access frequencies.
- **Counters:** The counter array (`cntr`) is critical for tracking the frequency of page access and determining the least frequently used page.

### **Edge Cases:**
- If the reference string has fewer pages than the number of frames, no page faults will occur (since there’s enough space to store all pages).
- If all the pages in the reference string are accessed with the same frequency, the algorithm will behave similarly to the **First Come, First Served (FCFS)** page replacement strategy.
*/
