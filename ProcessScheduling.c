#include <stdio.h>
#include <stdbool.h>

struct Process {
    char name[10];
    int arrival, burst, priority;
};

// Print Final Table
void printTable(struct Process p[], int finish[], int tat[], int wt[], int n) {
    printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].arrival, p[i].burst, finish[i], tat[i], wt[i]);
}

// ---------------- FCFS ----------------
void fcfs(struct Process p[], int n) {
    int finish[n], tat[n], wt[n], time = 0;

    printf("\n--- FCFS Scheduling ---\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) time = p[i].arrival;
        printf("| %s ", p[i].name);
        time += p[i].burst;
        finish[i] = time;
        tat[i] = finish[i] - p[i].arrival;
        wt[i] = tat[i] - p[i].burst;
    }

    printf("|\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) time = p[i].arrival;
        time += p[i].burst;
        printf("   %d", time);
    }
    printf("\n");

    printTable(p, finish, tat, wt, n);
}

// ---------------- SJF Non-Preemptive ----------------
void sjf_np(struct Process p[], int n) {
    int finish[n], tat[n], wt[n], time = 0, doneCount = 0;
    bool done[n];
    for (int i = 0; i < n; i++) done[i] = false;

    printf("\n--- SJF Non-Preemptive ---\nGantt Chart:\n");

    while (doneCount < n) {
        int idx = -1, minBT = 9999;

        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].arrival <= time && p[i].burst < minBT) {
                minBT = p[i].burst;
                idx = i;
            }

        if (idx == -1) { time++; continue; }

        printf("| %s ", p[idx].name);
        time += p[idx].burst;
        finish[idx] = time;
        tat[idx] = finish[idx] - p[idx].arrival;
        wt[idx] = tat[idx] - p[idx].burst;
        done[idx] = true;
        doneCount++;
    }

    printf("|\n0");
    time = 0;
    for (int i = 0; i < n; i++)
        if (finish[i] > time) { time = finish[i]; printf("   %d", time); }

    printf("\n");
    printTable(p, finish, tat, wt, n);
}

// ---------------- SJF Preemptive ----------------
void sjf_p(struct Process p[], int n) {
    int rem[n], finish[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) rem[i] = p[i].burst;

    int time = 0, completed = 0, last = -1;

    printf("\n--- SJF Preemptive ---\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1, minBT = 9999;

        for (int i = 0; i < n; i++)
            if (rem[i] > 0 && p[i].arrival <= time && rem[i] < minBT) {
                minBT = rem[i];
                idx = i;
            }

        if (idx == -1) { time++; continue; }

        if (last != idx) printf("| %s ", p[idx].name);
        last = idx;

        rem[idx]--;
        time++;

        if (rem[idx] == 0) {
            finish[idx] = time;
            tat[idx] = finish[idx] - p[idx].arrival;
            wt[idx] = tat[idx] - p[idx].burst;
            completed++;
        }
    }
    printf("|\n0   %d\n", time);

    printTable(p, finish, tat, wt, n);
}

// ---------------- Priority Non-Preemptive ----------------
void priority_np(struct Process p[], int n) {
    int finish[n], tat[n], wt[n], time = 0, doneCount = 0;
    bool done[n];
    for (int i = 0; i < n; i++) done[i] = false;

    printf("\n--- Priority Non-Preemptive ---\nGantt Chart:\n");

    while (doneCount < n) {
        int idx = -1, maxPR = -9999;

        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].arrival <= time && p[i].priority > maxPR) {
                maxPR = p[i].priority;
                idx = i;
            }

        if (idx == -1) { time++; continue; }

        printf("| %s ", p[idx].name);
        time += p[idx].burst;
        finish[idx] = time;
        tat[idx] = finish[idx] - p[idx].arrival;
        wt[idx] = tat[idx] - p[idx].burst;
        done[idx] = true;
        doneCount++;
    }

    printf("|\n0   %d\n", time);

    printTable(p, finish, tat, wt, n);
}

// ---------------- Priority Preemptive ----------------
void priority_p(struct Process p[], int n) {
    int rem[n], finish[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) rem[i] = p[i].burst;

    int time = 0, completed = 0, last = -1;

    printf("\n--- Priority Preemptive ---\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1, maxPR = -9999;

        for (int i = 0; i < n; i++)
            if (rem[i] > 0 && p[i].arrival <= time && p[i].priority > maxPR) {
                maxPR = p[i].priority;
                idx = i;
            }

        if (idx == -1) { time++; continue; }

        if (last != idx) printf("| %s ", p[idx].name);
        last = idx;

        rem[idx]--;
        time++;

        if (rem[idx] == 0) {
            finish[idx] = time;
            tat[idx] = finish[idx] - p[idx].arrival;
            wt[idx] = tat[idx] - p[idx].burst;
            completed++;
        }
    }
    printf("|\n0   %d\n", time);

    printTable(p, finish, tat, wt, n);
}

// ---------------- Round Robin ----------------
void roundRobin(struct Process p[], int n, int q) {
    int rem[n], finish[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) rem[i] = p[i].burst;

    int time = 0, completed = 0;
    printf("\n--- Round Robin (Quantum = %d) ---\n", q);

    printf("\nQueue Status:\n");
    printf("Time %d: [", time);
    for(int i=0;i<n;i++) if(p[i].arrival<=time) printf("%s ",p[i].name);
    printf("]\n");

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && p[i].arrival <= time) {
                idle = 0;
                printf("| %s ", p[i].name);

                if (rem[i] > q) {
                    rem[i] -= q;
                    time += q;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    finish[i] = time;
                    tat[i] = finish[i] - p[i].arrival;
                    wt[i] = tat[i] - p[i].burst;
                    completed++;
                }

                printf("\nTime %d: [", time);
                for(int j=0;j<n;j++)
                    if(rem[j]>0 && p[j].arrival<=time)
                        printf("%s ",p[j].name);
                printf("]\n");
            }
        }
        if (idle) time++;
    }

    printf("|\n0   %d\n", time);
    printTable(p, finish, tat, wt, n);
}

// ---------------- MAIN ----------------
int main() {
    int choice, n;

    printf("\nCPU Scheduling Algorithms:\n");
    printf("1.FCFS\n2.SJF NP\n3.SJF Preemptive\n4.Priority NP\n5.Priority Preemptive\n6.Round Robin\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d name: ", i+1);
        scanf("%s", p[i].name);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        if (choice == 4 || choice == 5) {
            printf("Priority: ");
            scanf("%d", &p[i].priority);
        }
    }

    int quantum;
    if (choice == 6) {
        printf("Enter Time Quantum: ");
        scanf("%d", &quantum);
    }

    switch(choice) {
        case 1: fcfs(p, n); break;
        case 2: sjf_np(p, n); break;
        case 3: sjf_p(p, n); break;
        case 4: priority_np(p, n); break;
        case 5: priority_p(p, n); break;
        case 6: roundRobin(p, n, quantum); break;
        default: printf("Invalid Choice!");
    }
    return 0;
}
