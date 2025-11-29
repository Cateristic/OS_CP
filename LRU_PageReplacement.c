#include <stdio.h>

int main() {
    int frames, n, i, j, k, pageFaults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    int ref[n], memory[frames], used[frames];

    printf("Enter reference string values:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    // Initialize memory frames as empty
    for (i = 0; i < frames; i++)
        memory[i] = -1;

    printf("\n--- LRU Page Replacement ---");
    printf("\nRef\tFrames\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check if page exists (hit)
        for (j = 0; j < frames; j++) {
            if (memory[j] == ref[i]) {
                found = 1;
                used[j] = i;  // Update last used time
                break;
            }
        }

        // Page Fault Case
        if (!found) {
            int pos = -1;

            // Find an empty frame first
            for (j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame => replace LRU
            if (pos == -1) {
                int minUsed = 9999;
                for (j = 0; j < frames; j++) {
                    if (used[j] < minUsed) {
                        minUsed = used[j];
                        pos = j;
                    }
                }
            }

            memory[pos] = ref[i];
            used[pos] = i;
            pageFaults++;
        }

        // Print output table
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
