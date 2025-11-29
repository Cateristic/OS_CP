#include <stdio.h>
#include <windows.h>

HANDLE mutex;    // For protecting readerCount
HANDLE wrt;      // Writer lock
int readerCount = 0;
int sharedData = 0;

DWORD WINAPI reader(LPVOID param) {
    int id = (int)param;

    WaitForSingleObject(mutex, INFINITE);
    readerCount++;

    if (readerCount == 1)
        WaitForSingleObject(wrt, INFINITE);

    ReleaseMutex(mutex);

    printf("Reader %d is reading shared data = %d\n", id, sharedData);
    Sleep(1000);

    WaitForSingleObject(mutex, INFINITE);
    readerCount--;

    if (readerCount == 0)
        ReleaseMutex(wrt);

    ReleaseMutex(mutex);

    return 0;
}

DWORD WINAPI writer(LPVOID param) {
    int id = (int)param;

    WaitForSingleObject(wrt, INFINITE);

    sharedData++;
    printf(" Writer %d updated shared data to %d\n", id, sharedData);
    Sleep(1000);

    ReleaseMutex(wrt);

    return 0;
}

int main() {
    HANDLE readers[5], writers[3];

    mutex = CreateMutex(NULL, FALSE, NULL);
    wrt   = CreateMutex(NULL, FALSE, NULL);

    printf("Starting Reader-Writer Simulation...\n\n");

    for (int i = 0; i < 5; i++) {
        readers[i] = CreateThread(NULL, 0, reader, (LPVOID)(i + 1), 0, NULL);
        Sleep(500); // Small delay to see interactions
    }

    for (int i = 0; i < 3; i++) {
        writers[i] = CreateThread(NULL, 0, writer, (LPVOID)(i + 1), 0, NULL);
        Sleep(1000);
    }

    WaitForMultipleObjects(5, readers, TRUE, INFINITE);
    WaitForMultipleObjects(3, writers, TRUE, INFINITE);

    CloseHandle(mutex);
    CloseHandle(wrt);

    return 0;
}
