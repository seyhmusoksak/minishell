#include "minishell.h"
#include <stdio.h>


int main ()
{
	char *str = "echo \"mehmet nasim | deneme\" | > a";
	printf("%s\n",ft_strchr(str,'t'));
}
