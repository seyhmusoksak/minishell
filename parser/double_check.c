/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:54:48 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/15 19:35:54 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	ft_double_quatition(char *str, int len)
{
	int	i;
	int	j;
	int	check;
	char *tmp;

	i = -1;
	check = 0;
	while (str[++i] && i < len)
	{
		if (str[i] == '"'  && ft_single_len(str, i) % 2 == 0)
		{
			printf("i: %d\n",i);
			j = i;
			while (str[++j] && j < len)
			{
				printf("anannın\n");
				if (str[j] == '"' ||  str[j+1] == '\0')
				{
					printf("c(%d)->%c\n",j,str[j]);
					tmp = ft_substr(str, i, (i - j));
					printf("tmp_double------>%s\n",tmp);
					check = 1;
					i = j;
				}
			if (ft_double_helper(tmp, &check) || (str[i] == '"' && str[i+1] == '\0'))
				return(1);
			}
		}
	}
	return (0);
}

int	ft_double_helper(char *str, int *check)
{
	if (*check == 1)
	{
		printf("double_helper\n");
		printf("str_double: %s\n",str);
		if (str != NULL && ft_double_len(str , (int) ft_strlen(str)) % 2 != 0)
		{
			printf("if1\n");
			free(str);
			return(1);
		}
		else
		{
			printf("if2\n");
			printf("x::::::::::%d\n",ft_double_len(str , (int) ft_strlen(str)) % 2);
			free(str);
			*check = 0;
			return(0);
		}
	}
	return (0);
}
int	ft_double_len(char *str, int len)
{
	int	i;
	int	dbl;

	dbl = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '"')
			dbl++;
		i++;
	}
	return(dbl);
}
