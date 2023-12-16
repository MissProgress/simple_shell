#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * Function to display the shell prompt
 */
void displayPrompt() {
    printf("#cisfun$ ");
}

/**
 * Function to read a line of input from the user
 */
char *readLine() {
    char *buffer = NULL;
    size_t bufferSize = 0;
    getline(&buffer, &bufferSize, stdin);
    return buffer;
}

/**
 * Function to execute a command entered by the user
 */
void executeCommand(char *command) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execlp(command, command, (char *)NULL) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main(void) {
    char *command;

    do {
        displayPrompt();
        command = readLine();

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            // Exit the shell if the user enters "exit"
            free(command);
            exit(EXIT_SUCCESS);
        }

        executeCommand(command);

        free(command);
    } while (1);

    return 0;
}

