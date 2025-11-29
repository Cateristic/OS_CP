#include <stdio.h>
#include <windows.h>

int main() {

    // -------- FILE SYSTEM CALL DEMO --------
    HANDLE file;
    DWORD bytesWritten, bytesRead;
    char writeData[] = "Hello, this is OS System Call Demo!";
    char readBuffer[100] = {0};

    printf("---- FILE SYSTEM CALL DEMO ----\n");

    // Create/Open a file
    file = CreateFile(
        "demo.txt",          // File name
        GENERIC_WRITE | GENERIC_READ,  
        0,                  
        NULL,               
        CREATE_ALWAYS,       
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (file == INVALID_HANDLE_VALUE) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write to the file
    WriteFile(file, writeData, sizeof(writeData), &bytesWritten, NULL);
    printf("Data Written: %s\n", writeData);

    // Move file pointer to beginning before reading
    SetFilePointer(file, 0, NULL, FILE_BEGIN);

    // Read from file
    ReadFile(file, readBuffer, sizeof(readBuffer), &bytesRead, NULL);
    printf("Data Read: %s\n", readBuffer);

    // Close the file
    CloseHandle(file);


    // -------- PROCESS SYSTEM CALL DEMO --------
    printf("\n\n---- PROCESS SYSTEM CALL DEMO ----\n");

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a new child process (Notepad example)
    if (CreateProcess(
        NULL,
        "notepad.exe",   // Program to run
        NULL, NULL, FALSE,
        0, NULL, NULL,
        &si, &pi
    )) {
        printf("Notepad started. Waiting for it to close...\n");

        // Wait for the child process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);

        printf("Child process finished.\n");

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("Failed to create process.\n");
    }

    return 0;
}
