#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    // ---------------- FILE SYSTEM CALLS ----------------
    printf("---- FILE SYSTEM CALL DEMO ----\n");

    int file;
    char writeData[] = "Hello, OS System Call Demo!";
    char readBuffer[100];

    // open() system call
    file = open("demo.txt", O_CREAT | O_RDWR, 0777);

    if (file < 0) {
        printf("File could not be opened!\n");
        return 1;
    }

    // write() system call
    write(file, writeData, sizeof(writeData));
    printf("Data Written: %s\n", writeData);

    // Move file pointer to start before reading
    lseek(file, 0, SEEK_SET);

    // read() system call
    read(file, readBuffer, sizeof(readBuffer));
    printf("Data Read: %s\n", readBuffer);

    // close() system call
    close(file);


    // ---------------- PROCESS SYSTEM CALLS ----------------
    printf("\n\n---- PROCESS SYSTEM CALL DEMO ----\n");

    pid_t pid = fork();  // fork() creates a child process

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child process running with PID: %d\n", getpid());
        printf("Child says Hello!\n");
        sleep(2);
    }
    else {
        // Parent process waits for child
        wait(NULL);
        printf("Parent process waiting completed. Child finished.\n");
    }

    return 0;
}
