#include <stdio.h>
#include <windows.h>

#define NUM_PHILOSOPHERS 5

HANDLE chopstick[NUM_PHILOSOPHERS];
HANDLE philosophers[NUM_PHILOSOPHERS];
int mode = 0; // 1 = deadlock, 2 = safe solution

DWORD WINAPI philosopher(LPVOID param) {
    int id = (int)param;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        Sleep(1000);

        printf("Philosopher %d is hungry...\n", id);

        if (mode == 1) {
            // 🔥 Deadlock scenario: All pick left fork first
            WaitForSingleObject(chopstick[id], INFINITE);
            WaitForSingleObject(chopstick[(id + 1) % NUM_PHILOSOPHERS], INFINITE);
        } else {
            // 🛡️ Safe solution: Break circular wait
            if (id == 0) {
                WaitForSingleObject(chopstick[(id + 1) % NUM_PHILOSOPHERS], INFINITE);
                WaitForSingleObject(chopstick[id], INFINITE);
            } else {
                WaitForSingleObject(chopstick[id], INFINITE);
                WaitForSingleObject(chopstick[(id + 1) % NUM_PHILOSOPHERS], INFINITE);
            }
        }

        printf("🍽 Philosopher %d is eating...\n", id);
        Sleep(2000);

        ReleaseMutex(chopstick[id]);
        ReleaseMutex(chopstick[(id + 1) % NUM_PHILOSOPHERS]);
    }

    return 0;
}

int main() {

    printf("\n===== Dining Philosophers Simulation =====\n");
    printf("1. Run Deadlock Version\n");
    printf("2. Run Deadlock-Free Version\n");
    printf("Enter your choice: ");
    scanf("%d", &mode);

    if (mode != 1 && mode != 2) {
        printf("Invalid choice! Exiting...\n");
        return 0;
    }

    if (mode == 1)
        printf("\n🔥 Starting DEADLOCK Scenario...\n\n");
    else
        printf("\n🛡️ Starting Deadlock-Free Scenario...\n\n");

    // Create mutex chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        chopstick[i] = CreateMutex(NULL, FALSE, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        philosophers[i] = CreateThread(NULL, 0, philosopher, (LPVOID)i, 0, NULL);

    // Wait for all threads (infinite simulation)
    WaitForMultipleObjects(NUM_PHILOSOPHERS, philosophers, TRUE, INFINITE);

    return 0;
}
