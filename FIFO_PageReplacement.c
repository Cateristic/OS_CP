#include <stdio.h>

int main() {
    int frames, n, i, j, k, pageFaults = 0;
    
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    int ref[n], memory[frames], pointer = 0;

    printf("Enter reference string values:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    // Initialize frames with -1 (empty)
    for (i = 0; i < frames; i++)
        memory[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");
    printf("\nRef\tFrames\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check if page already exists in frame
        for (j = 0; j < frames; j++) {
            if (memory[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        // Page fault occurs
        if (!found) {
            memory[pointer] = ref[i];
            pointer = (pointer + 1) % frames;
            pageFaults++;
        }

        // Display current frame status
        printf("%d\t", ref[i]);
        for (k = 0; k < frames; k++) {
            if (memory[k] == -1)
                printf("- ");
            else
                printf("%d ", memory[k]);
        }

        if (!found)
            printf(" <-- Page Fault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
