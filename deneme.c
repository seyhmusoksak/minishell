#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"

int main() {
	char cwd[1024];
	getcwd(cwd,1024);
	char *aa;
	DIR *dir;
    struct dirent *entry;

    // Dizin açma
	aa = ft_strjoin(cwd, "aa");
    dir = opendir(aa);

    if (dir == NULL) {
        perror("Users");
        return 1;
    }

    // Dizindeki her bir girişi okuma
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Dizini kapatma
    closedir(dir);

    return 0;
}
