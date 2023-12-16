#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

int main() {
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

        // Execute the command using execve
        if (execlp(command, command, (char *)NULL) == -1) {
            // Handle command not found
            printf("./shell: No such file or directory\n");
        }
    }

    return 0;
}

