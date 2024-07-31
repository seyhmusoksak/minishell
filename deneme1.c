#include <unistd.h>
#include <stdio.h>

int main() {
    char *const argv[] = {"2.txt", NULL};
    char *const envp[] = {NULL};

    if (execve("/bin/cat", argv, envp) == -1) {
        perror("execve");
        return 1;
    }

    return 0;
}

