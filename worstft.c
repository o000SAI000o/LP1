#include <stdio.h>
#define max 25

int main() {
    int frag[max], b[max], f[max], i, j, nb, nf, temp, highest;
    static int bf[max], ff[max];

    printf("\n\tMemory Management Scheme - Worst Fit");
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

    // Worst Fit Allocation
    for (i = 1; i <= nf; i++) {
        highest = -1; // Reset highest for each file
        int blockIndex = -1;

        // Find the block with the largest available space that can fit the file
        for (j = 1; j <= nb; j++) {
            if (bf[j] == 0) { // Block is unallocated
                temp = b[j] - f[i];
                if (temp >= 0 && temp > highest) { // Check for worst fit
                    highest = temp;
                    blockIndex = j;
                }
            }
        }

        // If a suitable block is found
        if (blockIndex != -1) {
            ff[i] = blockIndex; // Assign block number to file
            frag[i] = highest; // Fragmentation for this file
            b[blockIndex] -= f[i]; // Update block size after allocation
        } else {
            frag[i] = -1; // No suitable block found
        }
    }

    // Output the allocation details
    printf("\nFile No.\tFile Size\tBlock No.\tRemaining Block Size\tFragment");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != -1) {
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
        } else {
            printf("\n%d\t\t%d\t\tNot Allocated", i, f[i]);
        }
    }

    return 0;
}



/*Memory Management Scheme - Worst Fit
Enter number of Blocks: 5
Enter number of Files: 4

Enter Size of Blocks:
Block 1: 100
Block 2: 500
Block 3: 200
Block 4: 300
Block 5: 600

Enter Size of Files:
File 1: 212
File 2: 417
File 3: 112
File 4: 476

File No.	File Size	Block No.	Remaining Block Size	Fragment
1		212		5		276			388
2		417		2		83			83
3		112		5		276			276
4		476		Not Allocated


The code you provided implements the **Worst Fit** memory allocation algorithm. Here's an explanation of how it works and what the code does:

### Worst Fit Memory Allocation Algorithm:
The **Worst Fit** allocation strategy allocates a file to the block that has the **largest available space** that is large enough to accommodate the file. The goal is to leave the largest remaining space after allocation, hoping that it will be large enough to hold future files.

### Code Explanation:

1. **Variables:**
   - `frag[max]`: Array to store the fragmentation (unused space) after file allocation in each block.
   - `b[max]`: Array to store the size of each block.
   - `f[max]`: Array to store the size of each file.
   - `bf[max]`: Array to mark the status of blocks (whether allocated or not).
   - `ff[max]`: Array to store the block allocated to each file (or `-1` if no block is allocated).

2. **Input:**
   - The program first asks for the number of blocks (`nb`) and the number of files (`nf`).
   - Then, it asks for the size of each block and file.
   - Each block is initialized to `0` (unallocated) in `bf`, and each file is initialized to `-1` (unallocated) in `ff`.

3. **Worst Fit Allocation Logic:**
   - For each file, the program tries to find the block with the **largest available space** that can fit the file.
   - It calculates the remaining space (`temp = b[j] - f[i]`) for each block and chooses the block that has the maximum remaining space, ensuring the file fits.
   - If a block is found, the file is allocated to that block:
     - The block size is updated after allocation.
     - The fragmentation (remaining space after allocation) is calculated for the file and stored in the `frag` array.
   - If no block can accommodate the file, the file is marked as "Not Allocated".

4. **Output:**
   - After all files are processed, the program displays the allocation details for each file:
     - File number, file size, allocated block number, remaining block size after allocation, and fragmentation.
     - If a file is not allocated, it displays "Not Allocated".

### Sample Output Walkthrough:

**Input:**
- Number of Blocks: 5
- Number of Files: 4
- Block Sizes: 100, 500, 200, 300, 600
- File Sizes: 212, 417, 112, 476

**Step-by-Step Allocation:**
1. **File 1 (212)**:
   - It will be allocated to **Block 5** (size 600), leaving 388 units of space (fragmentation: 388).
   
2. **File 2 (417)**:
   - It will be allocated to **Block 2** (size 500), leaving 83 units of space (fragmentation: 83).
   
3. **File 3 (112)**:
   - It will be allocated to **Block 5** (size 388), leaving 276 units of space (fragmentation: 276).
   
4. **File 4 (476)**:
   - No block can accommodate this file because all the remaining blocks are too small. Hence, **Not Allocated**.

**Output:**
```
File No.    File Size    Block No.    Remaining Block Size    Fragment
1           212          5            276                     388
2           417          2            83                      83
3           112          5            276                     276
4           476          Not Allocated
```

### Key Points:
- **Worst Fit** tries to leave the largest remaining free space, hoping to avoid fragmentation in future allocations.
- This method may not always be the most efficient because it leaves large chunks of unused space that may not be used efficiently later.
- The program dynamically updates the sizes of blocks and files, and properly keeps track of the allocation and fragmentation.

### Conclusion:
This code implements the **Worst Fit Memory Allocation** scheme for managing file allocations in memory blocks. It helps in simulating how files would be allocated to memory blocks in real systems following this approach.
*/

