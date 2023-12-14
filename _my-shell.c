#include "myshell.h"
/**
 * main - creating my shell
 * Return: void
 */
int main(void)
{
	char input[MAX_SIZEIN];
	pid_t mpid;
	const char newline = '\n';
	const char *shellexit = "Exiting shell.\n";

	while (1)
	{
	my_prompt();
		/* Read a line from the user */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (feof(stdin))
			{
				write(1, &newline, 1);
				break;
			}
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}
		/* Remove newline character */
		input[strcspn(input, "\n")] = '\0';

		/* Fork a child process*/
		mpid = fork();
		if (mpid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (mpid == 0)
		{
			/* Child process*/
			execlp(input, input, NULL);
			/* If exec fails */
			perror("Command not found");
			exit(EXIT_FAILURE);
		}
	}
	write(1, shellexit, 15);
	return (0);
}
