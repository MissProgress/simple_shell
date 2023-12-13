#include "shell.h"

void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        display_prompt();

        // Read a line from the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (feof(stdin)) {
                // Handle end of file (Ctrl+D)
                printf("\n");
                break;
            }
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        // Remove newline character
        input[strcspn(input, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(input, input, NULL);

            // If exec fails
            perror("Command not found");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                // Child process exited normally
                printf("process exited with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                // Child process terminated by a signal
                printf("Process terminated by signal %d\n", WTERMSIG(status));
            }
        }
    }

    printf("Exiting shell.\n");
    return 0;
}

