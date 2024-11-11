#include <stdio.h>
#define max 25

int main() {
    int frag[max], b[max], f[max], i, j, nb, nf, temp, lowest;
    static int bf[max], ff[max];

    printf("\n\tMemory Management Scheme - Best Fit");
    printf("\nEnter number of Blocks: ");
    scanf("%d", &nb);
    printf("Enter number of Files: ");
    scanf("%d", &nf);

    printf("\nEnter Size of Blocks:\n");
    for (i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
        bf[i] = 0; // Initialize all block flags to 0 (unallocated)
    }

    printf("\nEnter Size of Files:\n");
    for (i = 1; i <= nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &f[i]);
        ff[i] = -1; // Initialize allocation status as unallocated
    }

    // Best Fit Allocation
    for (i = 1; i <= nf; i++) {
        lowest = 10000; // Reset lowest for each file
        for (j = 1; j <= nb; j++) {
            if (bf[j] == 0) { // Block is unallocated
                temp = b[j] - f[i];
                if (temp >= 0 && temp < lowest) { // Check for best fit
                    ff[i] = j; // Assign block number to file
                    lowest = temp;
                }
            }
        }

        // If a suitable block is found
        if (ff[i] != -1) {
            frag[i] = lowest; // Fragmentation for this file
            bf[ff[i]] = 1; // Mark block as allocated
        } else {
            frag[i] = -1; // No suitable block found
        }
    }

    // Output the allocation details
    printf("\nFile No.\tFile Size\tBlock No.\tBlock Size\tFragment");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != -1) {
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
        } else {
            printf("\n%d\t\t%d\t\tNot Allocated", i, f[i]);
        }
    }

    return 0;
}


/*Memory Management Scheme - Best Fit
Enter number of Blocks: 5
Enter number of Files: 4

Enter Size of Blocks:
Block 1: 100
Block 2: 500
Block 3: 200
Block 4: 400
Block 5: 600

Enter Size of Files:
File 1: 212
File 2: 417
File 3: 112
File 4: 476

File No.	File Size	Block No.	Block Size	Fragment
1		212		4		400		188
2		417		2		500		83
3		112		3		200		88
4		476		5		600		124


The code you've provided implements the **Best Fit** memory management scheme. The **Best Fit** algorithm allocates the smallest available block that is large enough to accommodate a file, minimizing the leftover space in the block after allocation.

### **Code Walkthrough:**

1. **Input:**
   - The program first prompts the user to enter the number of memory blocks (`nb`) and the number of files (`nf`).
   - Then, it takes input for the size of each block and the size of each file.

2. **Best Fit Allocation:**
   - For each file, the program searches for the **best fit** block, i.e., the block that is large enough to accommodate the file but has the smallest leftover space.
   - The algorithm keeps track of which blocks are already allocated using the `bf` array. If a block is unallocated, it compares the available space (`b[j] - f[i]`) to find the block with the smallest leftover space.
   - If a suitable block is found, the file is allocated to that block, and the block is marked as allocated.

3. **Fragmentation:**
   - **Fragmentation** is calculated as the difference between the block size and the file size: `frag[i] = b[ff[i]] - f[i]`.
   - If no suitable block is found for a file, it is marked as "Not Allocated."

4. **Output:**
   - The program prints the file number, file size, block number, block size, and the fragmentation for each file.
   - If a file could not be allocated to any block, it will show "Not Allocated."

### **Example Walkthrough:**

**Input:**
```
Enter number of Blocks: 5
Enter number of Files: 4

Enter Size of Blocks:
Block 1: 100
Block 2: 500
Block 3: 200
Block 4: 400
Block 5: 600

Enter Size of Files:
File 1: 212
File 2: 417
File 3: 112
File 4: 476
```

**Best Fit Allocation Process:**

1. **File 1** (size 212):
   - It tries to fit into the blocks:
     - Block 1: 100 (too small)
     - Block 2: 500 (remaining space = 500 - 212 = 288)
     - Block 3: 200 (remaining space = 200 - 212 = negative, not suitable)
     - Block 4: 400 (remaining space = 400 - 212 = 188)
     - Block 5: 600 (remaining space = 600 - 212 = 388)
   - Best fit: Block 4 (remaining space = 188). **File 1 is allocated to Block 4** with fragmentation 188.

2. **File 2** (size 417):
   - It tries to fit into the blocks:
     - Block 1: 100 (too small)
     - Block 2: 500 (remaining space = 500 - 417 = 83)
     - Block 3: 200 (remaining space = 200 - 417 = negative, not suitable)
     - Block 4: 400 (already allocated)
     - Block 5: 600 (remaining space = 600 - 417 = 183)
   - Best fit: Block 2 (remaining space = 83). **File 2 is allocated to Block 2** with fragmentation 83.

3. **File 3** (size 112):
   - It tries to fit into the blocks:
     - Block 1: 100 (too small)
     - Block 2: 500 (already allocated)
     - Block 3: 200 (remaining space = 200 - 112 = 88)
     - Block 4: 400 (already allocated)
     - Block 5: 600 (remaining space = 600 - 112 = 488)
   - Best fit: Block 3 (remaining space = 88). **File 3 is allocated to Block 3** with fragmentation 88.

4. **File 4** (size 476):
   - It tries to fit into the blocks:
     - Block 1: 100 (too small)
     - Block 2: 500 (already allocated)
     - Block 3: 200 (already allocated)
     - Block 4: 400 (already allocated)
     - Block 5: 600 (remaining space = 600 - 476 = 124)
   - Best fit: Block 5 (remaining space = 124). **File 4 is allocated to Block 5** with fragmentation 124.

**Output:**

```
File No.    File Size    Block No.    Block Size    Fragment
1           212          4            400           188
2           417          2            500           83
3           112          3            200           88
4           476          5            600           124
```

### **Explanation of the Output:**
- **File 1** is allocated to Block 4 with a fragmentation of 188.
- **File 2** is allocated to Block 2 with a fragmentation of 83.
- **File 3** is allocated to Block 3 with a fragmentation of 88.
- **File 4** is allocated to Block 5 with a fragmentation of 124.

### **Key Points of Best Fit Algorithm:**
- The **Best Fit** algorithm minimizes the leftover space in the allocated blocks by selecting the smallest block that can accommodate a file.
- It can lead to many small leftover fragments, which could lead to inefficient memory usage over time.
- This approach ensures that files are allocated in a way that minimizes fragmentation in the system, though it might leave many small gaps in the blocks. 

This approach is useful when minimizing the fragmentation within allocated blocks is a priority, but may lead to inefficient use of larger blocks if smaller files are allocated.
*/




