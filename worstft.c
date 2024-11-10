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
*/

