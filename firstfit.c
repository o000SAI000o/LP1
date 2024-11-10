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
*/
