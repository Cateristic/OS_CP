#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

HANDLE mutex;          // Mutual exclusion lock
HANDLE emptySlots;     // Semaphore -> available empty spaces
HANDLE fullSlots;      // Semaphore -> available items to consume

DWORD WINAPI producer(LPVOID param) {
    int id = (int)param;

    while (1) {
        int item = rand() % 100;

        // Wait if buffer is full
        WaitForSingleObject(emptySlots, INFINITE);

        // Lock shared buffer
        WaitForSingleObject(mutex, INFINITE);

        buffer[in] = item;
        printf(" Producer %d produced: %d at position %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);

        // Signal that one more full slot is available
        ReleaseSemaphore(fullSlots, 1, NULL);

        Sleep(1000);
    }

    return 0;
}

DWORD WINAPI consumer(LPVOID param) {
    int id = (int)param;

    while (1) {

        // Wait if buffer is empty
        WaitForSingleObject(fullSlots, INFINITE);

        // Lock shared buffer
        WaitForSingleObject(mutex, INFINITE);

        int item = buffer[out];
        printf(" Consumer %d consumed: %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);

        // Signal that one more empty slot is available
        ReleaseSemaphore(emptySlots, 1, NULL);

        Sleep(1500);
    }

    return 0;
}

int main() {
    HANDLE producers[2], consumers[2];

    mutex = CreateMutex(NULL, FALSE, NULL);
    emptySlots = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);  // Buffer initially empty
    fullSlots  = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);            // No items initially

    printf("Starting Producer Consumer Simulation...\n\n");

    for (int i = 0; i < 2; i++)
        producers[i] = CreateThread(NULL, 0, producer, (LPVOID)(i + 1), 0, NULL);

    for (int i = 0; i < 2; i++)
        consumers[i] = CreateThread(NULL, 0, consumer, (LPVOID)(i + 1), 0, NULL);

    WaitForMultipleObjects(2, producers, TRUE, INFINITE);
    WaitForMultipleObjects(2, consumers, TRUE, INFINITE);

    CloseHandle(mutex);
    CloseHandle(emptySlots);
    CloseHandle(fullSlots);

    return 0;
}
