#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

int main() {
	char cwd[1024];
	printf("%s\n",getcwd(cwd,sizeof(cwd)));
}
