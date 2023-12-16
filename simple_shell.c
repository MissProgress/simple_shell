#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        // Display the prompt
        printf("#cisfun$ ");

        // Read the command from the user
        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Handle "end of file" condition (Ctrl+D)
            printf("Exiting the shell.\n");
            exit(0);
        }

        // Remove the newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            if (execve(command, (char *[]){command, NULL}, NULL) == -1) {
                perror("Execve error");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}

