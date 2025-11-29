#include <stdio.h>
#include <stdbool.h>

struct Process {
    char name[10];
    int arrival, burst, priority;
};

int main() {
    int n, time = 0, completed = 0, last = -1;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int rem[n], finish[n], tat[n], wt[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nEnter Process Name: ");
        scanf("%s", p[i].name);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Enter Priority (Higher number = Higher priority): ");
        scanf("%d", &p[i].priority);

        rem[i] = p[i].burst; // remaining time
    }

    printf("\n--- Priority Scheduling (Preemptive) ---\n");
    printf("\nGantt Chart:\n");

    // Scheduling Loop
    while (completed < n) {
        int idx = -1, maxPriority = -9999;

        // Find highest priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && p[i].arrival <= time && p[i].priority > maxPriority) {
                maxPriority = p[i].priority;
                idx = i;
            }
        }

        // If no process has arrived yet, increment time
        if (idx == -1) {
            time++;
            continue;
        }

        // Print only when CPU switches process
        if (last != idx)
            printf("| %s ", p[idx].name);
        last = idx;

        rem[idx]--;
        time++;

        if (rem[idx] == 0) {
            finish[idx] = time;
            completed++;
        }
    }

    printf("|\n0   %d\n", time);

    // Compute TAT and WT
    for (int i = 0; i < n; i++) {
        tat[i] = finish[i] - p[i].arrival;
        wt[i] = tat[i] - p[i].burst;
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tPrio\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].arrival, p[i].burst, p[i].priority,
               finish[i], tat[i], wt[i]);
    }

    return 0;
}
