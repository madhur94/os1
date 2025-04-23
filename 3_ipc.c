#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

// Function to sort the file contents
void sort_file(int filedes) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        // Child process for sorting
        dup2(filedes, STDIN_FILENO);  // Redirect file as input to sort
        close(filedes);
        execlp("sort", "sort", NULL);  // Execute the sort command
        perror("execlp sort");
        exit(EXIT_FAILURE);
    }
    close(filedes);
    wait(NULL);  // Wait for the child process to complete
}

// Function to sort and remove duplicates (unique)
void sort_and_unique_file(int filedes, int fd[]) {
    pid_t pid;
    
    // First fork for sorting
    if ((pid = fork()) == 0) {
        // Child process for sorting first
        dup2(filedes, STDIN_FILENO);  // Redirect file as input to sort
        close(filedes);
        dup2(fd[1], STDOUT_FILENO);  // Redirect output to pipe
        close(fd[0]);
        execlp("sort", "sort", NULL);  // Execute the sort command
        perror("execlp sort");
        exit(EXIT_FAILURE);
    }

    close(filedes);
    close(fd[1]);

    // Second fork for uniq
    if ((pid = fork()) == 0) {
        // Child process for removing duplicates
        dup2(fd[0], STDIN_FILENO);  // Redirect pipe input to uniq
        close(fd[0]);
        execlp("uniq", "uniq", NULL);  // Execute the uniq command
        perror("execlp uniq");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    wait(NULL);  // Wait for the second child process to complete
    wait(NULL);  // Wait for the first child process to complete
}

// Function to handle file opening
int open_file(const char* filename) {
    int filedes = open(filename, O_RDONLY);
    if (filedes < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return filedes;
}

int main() {
    int fd[2];  // Pipe for communication between processes
    int choice;
    int filedes;

    do {
        // Display menu
        printf("Choose an option:\n");
        printf("1 - Sort only\n");
        printf("2 - Unique only\n");
        printf("3 - Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);

        // Open the source file for reading
        filedes = open_file("file.txt");

        // Create a pipe for communication between processes
        if (pipe(fd) == -1) {
            perror("pipe");
            close(filedes);
            exit(EXIT_FAILURE);
        }

        // Switch case to handle different operations based on user choice
        switch (choice) {
        case 1:  // Sort only
            sort_file(filedes);
            break;

        case 2:  // Unique only (with sort before uniq)
            sort_and_unique_file(filedes, fd);
            break;

        case 3:  // Exit
            printf("Exiting the program.\n");
            close(filedes);
            break;

        default:
            printf("Invalid choice! Please enter 1, 2, or 3.\n");
            close(filedes);
            break;
        }

        // Close the file descriptor after each operation
        close(filedes);

    } while (choice != 3);  // Repeat the menu until the user chooses to exit

    return 0;
}