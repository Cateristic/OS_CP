#include <stdio.h>
#include <stdbool.h>

struct Process {
    char name[10];
    int arrival, burst, priority;
};

int main() {
    int n, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int finish[n], tat[n], wt[n];
    bool done[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nEnter Process Name: ");
        scanf("%s", p[i].name);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Enter Priority (Higher number = Higher Priority): ");
        scanf("%d", &p[i].priority);
        done[i] = false;
    }

    printf("\n--- Priority Scheduling (Non-Preemptive) ---\n");
    printf("\nGantt Chart:\n");

    // Scheduling Loop
    while (completed < n) {
        int idx = -1, maxPriority = -9999;

        // Select process with highest priority among arrived ones
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].priority > maxPriority) {
                maxPriority = p[i].priority;
                idx = i;
            }
        }

        // If no process has arrived yet, increase time
        if (idx == -1) {
            time++;
            continue;
        }

        printf("| %s ", p[idx].name);

        time += p[idx].burst;
        finish[idx] = time;
        tat[idx] = finish[idx] - p[idx].arrival;
        wt[idx] = tat[idx] - p[idx].burst;

        done[idx] = true;
        completed++;
    }

    printf("|\n0   %d\n", time);

    // Result Table
    printf("\nProcess\tAT\tBT\tPrio\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].arrival, p[i].burst, p[i].priority,
               finish[i], tat[i], wt[i]);

    return 0;
}
