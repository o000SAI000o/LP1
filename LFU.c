#include <stdio.h>

int main() {
    int rs[50], i, j, k, m, f, cntr[20], a[20], min, pf = 0;

    // Input the number of page references
    printf("Enter number of page references: ");
    scanf("%d", &m);
    
    // Input the reference string
    printf("Enter the reference string: ");
    for(i = 0; i < m; i++) {
        scanf("%d", &rs[i]);
    }
   
    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    
    // Initialize frames and counters
    for(i = 0; i < f; i++) {
        cntr[i] = 0;  // Initialize reference counters to zero
        a[i] = -1;    // Initialize frames to empty
    }
    
    printf("\nThe Page Replacement Process is:\n");
    
    // LFU page replacement algorithm
    for(i = 0; i < m; i++) {
        int found = 0;
        
        // Check if page is already in a frame
        for(j = 0; j < f; j++) {
            if(rs[i] == a[j]) {
                cntr[j]++;  // Increment the use counter for LFU
                found = 1;
                break;
            }
        }
        
        // If page is not found, replace the least frequently used page
        if(!found) {
            // Find the frame with the smallest counter
            min = 0;
            for(k = 1; k < f; k++) {
                if(cntr[k] < cntr[min]) {
                    min = k;
                }
            }
            
            // Replace the page and reset its counter
            a[min] = rs[i];
            cntr[min] = 1;
            pf++;  // Increment page fault count
        }
        
        // Display current frame state
        for(j = 0; j < f; j++) {
            if(a[j] != -1) {
                printf("%d\t", a[j]);
            } else {
                printf("-\t");
            }
        }
        
        // Print page fault message if a replacement occurred
        if(!found) {
            printf("PF No. %d", pf);
        }
        
        printf("\n");
    }
    
    // Output the total number of page faults
    printf("\nTotal number of page faults: %d", pf);
    
    // Wait for user input before exiting (replaces getch())
    printf("\nPress Enter to exit...");
    getchar(); // Capture Enter key after scanf
    getchar(); // Capture the actual key press to pause
    return 0;
}

