#include <stdio.h>

int main() {
    int i, j, k, min, rs[25], m[10], count[10], flag[25], n, f, pf = 0, next = 1;
    
    // Input length of reference string
    printf("Enter the length of reference string: ");
    scanf("%d", &n);
    
    // Input the reference string
    printf("Enter the reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
        flag[i] = 0;
    }
    
    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    
    // Initialize frames and counters
    for(i = 0; i < f; i++) {
        count[i] = 0;
        m[i] = -1;
    }
    
    printf("\nThe Page Replacement Process is:\n");
    
    // LRU page replacement algorithm
    for(i = 0; i < n; i++) {
        int found = 0;
        
        // Check if page is already in memory
        for(j = 0; j < f; j++) {
            if(m[j] == rs[i]) {
                flag[i] = 1;
                count[j] = next;  // Update count for LRU
                next++;
                found = 1;
                break;
            }
        }
        
        // If page is not found, it’s a page fault
        if(!found) {
            int replace_index = -1;

            if (i < f) { // Initial filling of frames
                replace_index = i;
            } else { // Replace the LRU page
                min = 0;
                for(j = 1; j < f; j++) {
                    if(count[min] > count[j]) {
                        min = j;
                    }
                }
                replace_index = min;
            }

            m[replace_index] = rs[i];
            count[replace_index] = next;
            next++;
            pf++; // Increment page fault count
        }
        
        // Display current frame state
        for(j = 0; j < f; j++) {
            if(m[j] != -1) {
                printf("%d\t", m[j]);
            } else {
                printf("-\t");
            }
        }
        
        // Print page fault message if a page fault occurred
        if(!found) {
            printf("PF No. -- %d", pf);
        }
        
        printf("\n");
    }
    
    printf("\nThe number of page faults using LRU is: %d", pf);

    // Wait for user input to exit the program (replacing getch() functionality)
    printf("\nPress any key to exit...");
    getchar(); // To capture the "Enter" key press after printing results
    getchar(); // Capture the actual key press to pause
    return 0;
}

/*
The provided code implements the **Least Recently Used (LRU)** page replacement algorithm. LRU is a page replacement policy that replaces the least recently used page when a new page is referenced, and the memory is full.

### **Explanation of the Code:**

1. **Input:**
   - The length of the reference string (`n`) is taken as input.
   - The reference string (`rs`) is entered, which consists of page numbers that the process references.
   - The number of frames (`f`) is taken as input, which is the number of pages that can be held in memory at a time.

2. **Data Structures:**
   - `rs[25]`: Array to store the reference string.
   - `m[10]`: Array representing the frames in memory. Initially, it contains `-1` (indicating empty frames).
   - `count[10]`: Counter array used to track the time when a page is last accessed (for LRU).
   - `flag[25]`: Array to keep track of whether a page is found in memory (used to check if a page fault occurred).
   - `n`: Number of pages in the reference string.
   - `f`: Number of frames in memory.
   - `pf`: Page fault count, which increments every time a page is not found in memory.
   - `next`: Counter to simulate the passing of time when pages are accessed.

3. **Algorithm Steps:**
   - The frames are initialized to `-1` to represent empty slots.
   - The `count` array is initialized to `0` and tracks the "last used time" for each frame.
   - The **LRU algorithm** is implemented by checking if the page exists in any of the frames:
     - If the page is found in the frames, it updates the "last used time" for that page.
     - If the page is not found in the frames, a page fault occurs. The **LRU page** is replaced by the new page, and the `count` array is updated to reflect the current time.

4. **Frame Management:**
   - If there is space available in the frames (i.e., not all frames are filled yet), the page is simply placed in an empty slot.
   - If the frames are full, the **LRU page** (the page that was least recently used) is replaced by the new page. This is determined by comparing the `count` values for each frame.

5. **Display:**
   - After each page reference, the current contents of the frames are displayed.
   - If a page fault occurs, it is noted with a message displaying the page fault number (`PF No.`).

6. **Output:**
   - After processing the entire reference string, the total number of page faults is displayed.

### **Step-by-Step Example:**

Let’s walk through an example with the following input:

```
Enter the length of reference string: 12
Enter the reference string: 7 0 1 2 0 3 0 4 2 3 0 3
Enter the number of frames: 4
```

**Step-by-step Execution:**

1. **Initially, all frames are empty (`-1`):**
   ```
   -	-	-	-  
   ```

2. **Page 7:** 
   - The page is not in memory, so it's a page fault. It is placed in the first available frame.
   ```
   7	-	-	-
   PF No. -- 1
   ```

3. **Page 0:**
   - The page is not in memory, so it's a page fault. It is placed in the second available frame.
   ```
   7	0	-	-
   PF No. -- 2
   ```

4. **Page 1:**
   - The page is not in memory, so it's a page fault. It is placed in the third available frame.
   ```
   7	0	1	-
   PF No. -- 3
   ```

5. **Page 2:**
   - The page is not in memory, so it's a page fault. It is placed in the fourth available frame.
   ```
   7	0	1	2
   PF No. -- 4
   ```

6. **Page 0:** 
   - Page 0 is already in memory, so no page fault occurs. The "last used time" of page 0 is updated.
   ```
   7	0	1	2
   ```

7. **Page 3:**
   - Page 3 is not in memory. The least recently used page is 7, so it is replaced by 3.
   ```
   3	0	1	2
   PF No. -- 5
   ```

8. **Page 0:**
   - Page 0 is already in memory, so no page fault occurs. The "last used time" of page 0 is updated.
   ```
   3	0	1	2
   ```

9. **Page 4:**
   - Page 4 is not in memory. The least recently used page is 1, so it is replaced by 4.
   ```
   3	0	4	2
   PF No. -- 6
   ```

10. **Page 2:** 
    - Page 2 is already in memory, so no page fault occurs. The "last used time" of page 2 is updated.
    ```
    3	0	4	2
    ```

11. **Page 3:**
    - Page 3 is already in memory, so no page fault occurs. The "last used time" of page 3 is updated.
    ```
    3	0	4	2
    ```

12. **Final Output:**
    - Total page faults = 6

### **Output:**
```
The number of page faults using LRU is: 6
```

### **Key Concepts:**
- **Page Fault:** Occurs when a page that is required is not currently loaded into memory, causing the system to fetch it from disk and potentially replace another page.
- **LRU Algorithm:** The page that hasn't been used for the longest time is replaced when a new page needs to be loaded into memory.
- **Page Replacement:** In LRU, the least recently used page is replaced when a page fault occurs, ensuring that the most recently used pages stay in memory.

### **Edge Cases:**
- If there are fewer pages than frames, no page faults will occur, as each page will fit into an empty frame.
- If the reference string contains repeated pages, the page fault count will be lower as repeated pages will be found in memory without causing a fault.
*/
