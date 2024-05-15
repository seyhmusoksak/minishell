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


static void	ft_loop(t_env **ptr1, t_env **lptr, int *swapped, int (*cmp)(char *, char *))
{
	char	*temp;
	char	*tmpvalue;
	while ((*ptr1)->next != lptr)
	{
		if ((*cmp)((*ptr1)->key, (*ptr1)->next->key) > 0)
		{
			temp = (*ptr1)->key;
			tmpvalue = (*ptr1)->value;
			(*ptr1)->key = (*ptr1)->next->key;
			(*ptr1)->value = (*ptr1)->next->value;
			(*ptr1)->next->key = temp;
			(*ptr1)->next->value = tmpvalue;
			swapped = 0;
		}
		(*ptr1) = (*ptr1)->next;
	}
}
