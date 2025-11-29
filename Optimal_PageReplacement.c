#include <stdio.h>

int main() {
    int frames, n, i, j, k, pageFaults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    int ref[n], memory[frames];

    printf("Enter reference string values:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    // Initialize frames with -1 (empty)
    for (i = 0; i < frames; i++)
        memory[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");
    printf("\nRef\tFrames\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check if the page already exists (HIT)
        for (j = 0; j < frames; j++) {
            if (memory[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        // If page not found → page fault
        if (!found) {
            int pos = -1;

            // Step 1: Try empty frame
            for (j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // Step 2: If no empty frame → use optimal replacement logic
            if (pos == -1) {
                int farthest = -1;

                for (j = 0; j < frames; j++) {
                    int nextUse = -1;

                    // Find when this frame will be used again
                    for (k = i + 1; k < n; k++) {
                        if (memory[j] == ref[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    // If a page is never used again → replace it immediately
                    if (nextUse == -1) {
                        pos = j;
                        break;
                    }

                    if (nextUse > farthest) {
                        farthest = nextUse;
                        pos = j;
                    }
                }
            }

            memory[pos] = ref[i];
            pageFaults++;
        }

        // Print memory state
        printf("%d\t", ref[i]);
        for (k = 0; k < frames; k++) {
            if (memory[k] == -1)
                printf("- ");
            else
                printf("%d ", memory[k]);
        }
        if (!found)
            printf("<-- Page Fault");
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
