#include <stdio.h>
#define max 25

int main() {
    int frag[max], b[max], f[max], i, j, nb, nf;
    static int bf[max], ff[max];

    printf("\n\tMemory Management Scheme - First Fit");
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
        ff[i] = -1; // Initialize all file allocation to -1 (not allocated)
    }

    // First Fit Allocation
    for (i = 1; i <= nf; i++) { // Iterate over each file
        for (j = 1; j <= nb; j++) { // Check each block for the current file
            if (bf[j] == 0 && b[j] >= f[i]) { // Find first unallocated block that fits the file
                ff[i] = j; // Assign block number to file
                frag[i] = b[j] - f[i]; // Calculate fragmentation for this block
                b[j] -= f[i]; // Reduce block size by file size (update available space)
                break; // Move to next file once block is allocated
            }
        }
    }

    // Output the allocation details
    printf("\nFile No.\tFile Size\tBlock No.\tBlock Size Remaining\tFragment");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != -1) {
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
        } else {
            printf("\n%d\t\t%d\t\tNot Allocated", i, f[i]);
        }
    }
    return 0;
}






/*Memory Management Scheme - First Fit
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

File No.	File Size	Block No.	Block Size Remaining	Fragment
1		212		2		176			288
2		417		5		183			183
3		112		2		176			176
4		476		Not Allocated



The code you provided implements the **First Fit** memory allocation scheme. Here's an explanation of how it works and the corresponding output:

### **First Fit Memory Allocation Algorithm:**
The **First Fit** allocation strategy assigns a file to the **first block** that is large enough to accommodate the file. It scans through the blocks in order and allocates the file to the first block that has sufficient space.

### **Code Explanation:**

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

3. **First Fit Allocation Logic:**
   - For each file, the program checks each block to find the **first block** that is **unallocated** and has enough space to accommodate the file.
   - If such a block is found:
     - The file is allocated to that block.
     - The block size is updated by subtracting the file size, indicating the remaining space in the block.
     - The fragmentation (remaining space in the block after file allocation) is calculated and stored.
   - If no block can accommodate the file, the file is marked as "Not Allocated."

4. **Output:**
   - After all files are processed, the program displays the allocation details for each file:
     - File number, file size, allocated block number, remaining block size after allocation, and fragmentation.
     - If a file is not allocated, it displays "Not Allocated."

### **Sample Input and Output Walkthrough:**

**Input:**
- Number of Blocks: 5
- Number of Files: 4
- Block Sizes: 100, 500, 200, 300, 600
- File Sizes: 212, 417, 112, 476

**Step-by-Step Allocation:**
1. **File 1 (212)**:
   - The program checks the blocks one by one:
     - Block 1 (100) is too small.
     - Block 2 (500) is large enough, so File 1 is allocated to Block 2.
     - Block 2 size reduces to 500 - 212 = 288.
     - Fragmentation for File 1: 288 (remaining space in Block 2).
   
2. **File 2 (417)**:
   - The program checks the blocks:
     - Block 1 (100) is too small.
     - Block 2 (288) is too small (after File 1 allocation).
     - Block 3 (200) is too small.
     - Block 4 (300) is too small.
     - Block 5 (600) is large enough, so File 2 is allocated to Block 5.
     - Block 5 size reduces to 600 - 417 = 183.
     - Fragmentation for File 2: 183 (remaining space in Block 5).
   
3. **File 3 (112)**:
   - The program checks the blocks:
     - Block 1 (100) is too small.
     - Block 2 (288) is large enough, so File 3 is allocated to Block 2.
     - Block 2 size reduces to 288 - 112 = 176.
     - Fragmentation for File 3: 176 (remaining space in Block 2).
   
4. **File 4 (476)**:
   - The program checks the blocks:
     - Block 1 (100) is too small.
     - Block 2 (176) is too small.
     - Block 3 (200) is too small.
     - Block 4 (300) is too small.
     - Block 5 (183) is too small.
     - No suitable block is found, so File 4 is not allocated.

**Output:**
```
File No.    File Size    Block No.    Block Size Remaining    Fragment
1           212          2            176                     288
2           417          5            183                     183
3           112          2            176                     176
4           476          Not Allocated
```

### **Key Points:**
- **First Fit** looks for the first available block that can fit a file, without considering other blocks.
- This strategy is simple and fast but may cause fragmentation over time as it leaves smaller unutilized spaces in blocks.
- The program accurately tracks the allocation, remaining block sizes, and fragmentation.

### **Conclusion:**
This code implements the **First Fit Memory Allocation** scheme for managing file allocations in memory blocks. It's a simple and efficient way to allocate files, though it might not always be the most efficient in terms of space utilization, as it allocates files to the first available block without considering the best possible fit.
*/
