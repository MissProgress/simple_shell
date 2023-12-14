#include "myshell.h"

/**
 * my_prompt - constant display
 */
void my_prompt(void)
{
	const char *strToDispl = "#cisfun$ ";

	write(1, strToDispl, 9);
}
