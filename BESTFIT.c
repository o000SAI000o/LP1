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
*/




