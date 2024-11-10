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

