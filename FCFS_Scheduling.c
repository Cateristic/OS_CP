#include <stdio.h>

struct Process {
    char name[10];
    int arrival, burst;
};

int main() {
    int n, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int finish[n], tat[n], wt[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nEnter process name: ");
        scanf("%s", p[i].name);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);
    }

    // Sort processes by arrival time (FCFS rule)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // FCFS Scheduling
    printf("\n\n--- FCFS Scheduling ---\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;

        printf("| %s ", p[i].name);

        time += p[i].burst;
        finish[i] = time;
        tat[i] = finish[i] - p[i].arrival;
        wt[i] = tat[i] - p[i].burst;
    }

    printf("|\n0");
    time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        time += p[i].burst;
        printf("   %d", time);
    }

    // Output Table
    printf("\n\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].arrival, p[i].burst, finish[i], tat[i], wt[i]);

    return 0;
}
