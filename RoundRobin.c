#include <stdio.h>
#include <stdbool.h>

struct Process {
    char name[10];
    int arrival, burst;
};

int main() {
    int n, quantum, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int finish[n], tat[n], wt[n], rem[n];
    bool added[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nEnter Process Name: ");
        scanf("%s", p[i].name);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);
        rem[i] = p[i].burst;
        added[i] = false;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    printf("\n--- Round Robin Scheduling (Quantum = %d) ---\n", quantum);
    printf("\nQueue Trace and Execution Order:\n");

    printf("\nGantt Chart:\n");

    // Round Robin Processing Loop
    while (completed < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && p[i].arrival <= time) {
                idle = 0;
                printf("| %s ", p[i].name);

                if (rem[i] > quantum) {
                    rem[i] -= quantum;
                    time += quantum;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    finish[i] = time;
                    completed++;
                }

                printf("\nTime %d: [", time);
                for (int j = 0; j < n; j++)
                    if (rem[j] > 0 && p[j].arrival <= time)
                        printf("%s ", p[j].name);
                printf("]\n");
            }
        }

        if (idle)
            time++;
    }

    printf("|\n0   %d\n", time);

    // Calculate TAT & WT
    for (int i = 0; i < n; i++) {
        tat[i] = finish[i] - p[i].arrival;
        wt[i] = tat[i] - p[i].burst;
    }

    // Output Result Table
    printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].arrival, p[i].burst, finish[i], tat[i], wt[i]);

    return 0;
}
