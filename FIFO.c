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


	
Explanation of Output:




- Each line shows the state of the frames after each page request.
- The "Page Fault No." counter shows when a page fault occurs and how many page faults have occurred so far. 

This algorithm demonstrates FIFO, a simple page replacement strategy, though it may not be the most efficient for minimizing page faults in all cases.


### How FIFO (First-In-First-Out) Page Replacement Algorithm Works

FIFO (First-In-First-Out) is one of the simplest page replacement algorithms used in memory management to handle page faults. Here’s a step-by-step explanation of how it works:

### Key Concepts:
- **Pages**: These are the chunks of data being accessed by a program. They are loaded into **memory frames** for processing.
- **Page Fault**: This occurs when a program tries to access a page that is not currently in memory (i.e., the page is not in one of the available frames).
- **Memory Frames**: These are the slots or locations in memory where pages are stored temporarily.
- **FIFO Queue**: The FIFO algorithm maintains a queue-like structure where the first page loaded (or placed into memory) is the first one to be replaced when a page fault occurs.

### FIFO Algorithm Process

1. **Initial Setup**:
   - A fixed number of memory frames (slots) are available to store pages.
   - These frames are initially empty.
   
2. **Page Access**:
   - The program accesses pages in a specific sequence (the **reference string**).
   - For each page access, FIFO checks whether the page is already in one of the available frames.

3. **Page Hit**:
   - If the page being accessed is already in memory (in one of the frames), no page fault occurs, and the page remains in memory.
   
4. **Page Fault**:
   - If the page being accessed is **not** in memory (it is not present in any of the frames), a **page fault** occurs.
   - FIFO then replaces the page in the memory frame that has been there the longest (i.e., the **first-in** page). This page is replaced by the new one.
   - After replacing the page, the page that was replaced is now considered "evicted" from memory.
   
5. **FIFO Queue**:
   - FIFO essentially maintains a queue of pages in memory. The oldest page (the one that was loaded first) will be replaced first when a new page needs to be loaded into memory.

6. **Repeating the Process**:
   - The process continues for each page in the reference string until all pages are processed. After each page access, the frames are checked to see if they need to be updated.

### FIFO Example

Let’s go through a simple example to understand how FIFO works. Assume we have 3 frames and the reference string is:

```
Reference String: 7, 0, 1, 2, 0, 3, 0, 4
```

#### Step-by-Step Process:

1. **First page request: 7**
   - Frames: `- - -` (empty)
   - Page 7 is not in memory, so it’s placed in the first available frame.
   - Frames: `7 - -` (Page 7 is loaded)
   - Page Fault #1.

2. **Second page request: 0**
   - Frames: `7 - -`
   - Page 0 is not in memory, so it’s placed in the next available frame.
   - Frames: `7 0 -` (Page 0 is loaded)
   - Page Fault #2.

3. **Third page request: 1**
   - Frames: `7 0 -`
   - Page 1 is not in memory, so it’s placed in the next available frame.
   - Frames: `7 0 1` (Page 1 is loaded)
   - Page Fault #3.

4. **Fourth page request: 2**
   - Frames: `7 0 1`
   - Page 2 is not in memory, and we have no empty frames. So, the page that was loaded first (7) will be replaced.
   - Frames: `2 0 1` (Page 7 is replaced by Page 2)
   - Page Fault #4.

5. **Fifth page request: 0**
   - Frames: `2 0 1`
   - Page 0 is already in memory, so no replacement is needed.
   - No Page Fault.

6. **Sixth page request: 3**
   - Frames: `2 0 1`
   - Page 3 is not in memory, so the oldest page (1) will be replaced.
   - Frames: `2 0 3` (Page 1 is replaced by Page 3)
   - Page Fault #5.

7. **Seventh page request: 0**
   - Frames: `2 0 3`
   - Page 0 is already in memory, so no replacement is needed.
   - No Page Fault.

8. **Eighth page request: 4**
   - Frames: `2 0 3`
   - Page 4 is not in memory, and the oldest page (2) will be replaced.
   - Frames: `4 0 3` (Page 2 is replaced by Page 4)
   - Page Fault #6.

#### Final Frame Status:
```
Frames: 4 0 3
Total Page Faults: 6
```

### Summary of FIFO
- FIFO is simple and easy to implement.
- It replaces the oldest page when a page fault occurs.
- Its main disadvantage is that it does not consider the frequency of page accesses; it can replace pages that might be used again soon, leading to higher page fault rates in some cases.

FIFO is ideal for situations where simplicity and ease of implementation are more important than optimal page replacement performance. However, algorithms like **LRU (Least Recently Used)** or **Optimal Page Replacement** are generally more efficient in minimizing page faults.
