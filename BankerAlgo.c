#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m;
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int total[MAX_RESOURCES]; // <-- added to keep total resource count

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

// Modified isSafe() to show step-by-step Available updates
bool isSafe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSeq[MAX_PROCESSES];
    int count = 0;

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    printf("\nChecking Safe Sequence...\n");
    printf("\nStep\tProcess\tWork Before\tAllocated\tWork After\n");

    while (count < n) {
        bool found = false;

        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canAllocate = true;

                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    printf("%d\tP%d\t", count+1, p);

                    // Print work before allocation
                    for (int j = 0; j < m; j++)
                        printf("%d ", work[j]);

                    printf("\t\t");

                    // Add allocated resources back
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[p][k];

                    // Print allocated
                    for (int k = 0; k < m; k++)
                        printf("%d ", allocation[p][k]);

                    printf("\t\t");

                    // Print work after allocation
                    for (int j = 0; j < m; j++)
                        printf("%d ", work[j]);

                    printf("\n");

                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\n⚠ System is NOT in a safe state!\n");
            return false;
        }
    }

    printf("\n✔ System is in a SAFE STATE.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return true;
}


// Modified display function to show total instances
void displayData() {
    printf("\nProcess\tAllocation\tMaximum\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", allocation[i][j]);
        printf("\t\t");
        for (int j = 0; j < m; j++) printf("%d ", maximum[i][j]);
        printf("\t\t");
        for (int j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\nTotal Resources: ");
    for (int i = 0; i < m; i++) printf("%d ", total[i]);

    printf("\nAvailable Resources: ");
    for (int i = 0; i < m; i++) printf("%d ", available[i]);
    printf("\n");
}

void requestResources() {
    int p, request[MAX_RESOURCES];

    printf("Enter process number (0-%d): ", n - 1);
    scanf("%d", &p);

    printf("Enter requested instances:\n");
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &request[i]);
    }

    for (int i = 0; i < m; i++) {
        if (request[i] > need[p][i]) {
            printf("❌ Error: Request exceeds process maximum need.\n");
            return;
        }
        if (request[i] > available[i]) {
            printf("⛔ Request Denied: Resources Not Available.\n");
            return;
        }
    }

    // Tentative allocation
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    if (isSafe()) {
        printf("\n✔ Request APPROVED.\n");
    } else {
        printf("\n⛔ Request leads to unsafe state. Rolling back...\n");

        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[p][i] -= request[i];
            need[p][i] += request[i];
        }
    }
}

int main() {
    int choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter total instances of each resource:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &total[i]);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("\nEnter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &maximum[i][j]);
    }

    // Calculate available = total - allocated
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += allocation[i][j];
        available[j] = total[j] - sum;
    }

    calculateNeed();

    while (1) {
        printf("\n======= BANKER'S ALGORITHM MENU =======\n");
        printf("1. Display Matrices\n");
        printf("2. Check Safe State\n");
        printf("3. Request Resources\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayData(); break;
            case 2: isSafe(); break;
            case 3: requestResources(); break;
            case 4: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}
