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

