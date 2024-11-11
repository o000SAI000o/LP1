#include <stdio.h>

int main() {
    int i, j, k, f, pf = 0, count = 0, n;
    int rs[25], m[10];

    // Input length of reference string
    printf("\nEnter the length of reference string: ");
    scanf("%d", &n);
    
    // Input the reference string
    printf("Enter the reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
    }
    
    // Input number of frames
    printf("\nEnter number of frames: ");
    scanf("%d", &f);
    
    // Initialize frames to -1 (indicating empty frames)
    for(i = 0; i < f; i++) {
        m[i] = -1;
    }
    
    printf("\nThe Page Replacement Process is:\n");
    
    // FIFO page replacement algorithm
    for(i = 0; i < n; i++) {
        int found = 0;
        
        // Check if the page is already in frames
        for(k = 0; k < f; k++) {
            if(m[k] == rs[i]) {
                found = 1;
                break;
            }
        }
        
        // If page is not found, it is a page fault
        if(!found) {
            m[count] = rs[i]; // Replace the oldest page in FIFO manner
            count = (count + 1) % f; // Update count to point to the next frame in FIFO
            pf++; // Increment page fault count
        }
        
        // Print current state of frames
        for(j = 0; j < f; j++) {
            if(m[j] != -1) {
                printf("\t%d", m[j]);
            } else {
                printf("\t-");
            }
        }
        
        printf("\tPage Fault No. %d\n", pf);
    }
    
    printf("\nThe number of Page Faults using FIFO are: %d", pf);

    // No need for getch(), the program will end after this line
    return 0;
}




explanation:

This C program implements the **FIFO (First-In-First-Out) Page Replacement Algorithm** to simulate page replacement in memory management. Here’s a breakdown of how it works:

### Program Explanation

1. **Input Section**:
   - The program first prompts the user to enter the **length of the reference string** (number of pages requested).
   - The **reference string** itself is then entered, representing the sequence of pages the program will request.
   - Finally, the program asks for the **number of frames** (memory slots available to hold pages).

2. **Initialization**:
   - An array `m[]` is initialized to hold the pages in the frames. Initially, each frame is set to `-1` to indicate it’s empty.

3. **FIFO Page Replacement Process**:
   - The program iterates over each page request in the reference string (`rs[]`).
   - For each page request:
     - It checks if the page is already in one of the frames by searching `m[]`.
     - If the page is found, no action is taken (no page fault).
     - If the page is **not found in frames** (indicating a page fault):
       - The page is inserted into the frame pointed to by `count`, which represents the FIFO position.
       - `count` is then updated to point to the next frame in a circular manner using modulo operation, ensuring a FIFO replacement order.
       - The **page fault counter `pf`** is incremented to count this fault.

4. **Displaying Frame Status**:
   - After each page request, the program displays the current state of the frames, with `-` representing empty frames.
   - It also shows the page fault number if a page fault occurred.

5. **Final Output**:
   - Once all page requests are processed, the program prints the **total number of page faults** that occurred using the FIFO page replacement algorithm.

### Sample Output
For a clearer understanding, here’s what a sample run might look like:

```plaintext
Enter the length of reference string: 5
Enter the reference string: 1 2 3 1 4
Enter number of frames: 3

The Page Replacement Process is:
	1	-	-	Page Fault No. 1
	1	2	-	Page Fault No. 2
	1	2	3	Page Fault No. 3
	1	2	3	Page Fault No. 3
	4	2	3	Page Fault No. 4

The number of Page Faults using FIFO are: 4
```

### Explanation of Output
- Each line shows the state of the frames after each page request.
- The "Page Fault No." counter shows when a page fault occurs and how many page faults have occurred so far. 

This algorithm demonstrates FIFO, a simple page replacement strategy, though it may not be the most efficient for minimizing page faults in all cases.
