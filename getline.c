#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static size_t buffer_index = 0;
static size_t buffer_size = 0;

char* custom_getline(void) {
    if (buffer_index == buffer_size) {
        buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        buffer_index = 0;

        // If there's nothing more to read, return NULL
        if (buffer_size == 0) {
            return NULL;
        }
    }

    size_t start = buffer_index;
    while (buffer_index < buffer_size && buffer[buffer_index] != '\n') {
        buffer_index++;
    }

    char* line = malloc(buffer_index - start + 1);
    if (!line) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    size_t i, j;
    for (i = start, j = 0; i < buffer_index; i++, j++) {
        line[j] = buffer[i];
    }

    line[j] = '\0';

    buffer_index++;

    return line;
}

int main(void) {
    while (1) {
        char* line = custom_getline();

        if (line == NULL) {
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            char* args[2] = {line, NULL};
            execve(line, args, NULL);

            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, NULL, 0);
        }

        free(line);
    }

    return 0;
}

