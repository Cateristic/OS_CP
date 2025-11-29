#include <stdio.h>
#include <stdbool.h>

struct Process {
    char name[10];
    int arrival, burst;
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
        printf("\nEnter process name: ");
        scanf("%s", p[i].name);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);
        done[i] = false;
    }

    printf("\n\n--- SJF (Non-Preemptive) Scheduling ---\nGantt Chart:\n");

    // SJF Scheduling
    while (completed < n) {
        int idx = -1, minBT = 99999;

        // Select process with smallest burst among arrived ones
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].burst < minBT) {
                minBT = p[i].burst;
                idx = i;
            }
        }

        // If no process arrived yet, move time forward
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

    printf("|\n0");
    time = 0;

    // Print timeline
    for (int i = 0; i < n; i++)
        if (finish[i] > time) { time = finish[i]; printf("   %d", time); }

    // Result Table
    printf("\n\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].arrival, p[i].burst, finish[i], tat[i], wt[i]);

    return 0;
}
