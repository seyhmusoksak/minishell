#include <stdio.h>
#include <readline/readline.h>

int main() {
    char *input = readline("Enter a string: ");
    rl_redisplay();
	printf("%s",input);
    free(input);
    return 0;
}
