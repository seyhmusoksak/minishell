/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:54:48 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/15 19:22:56 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_qutation_len_check(char *str, int len)
{
	if (ft_singl_quatition(str, len))
		return (1);
	if (ft_double_quatition(str, len))
		return(1);
	// else if ()
	return (0);
}
// int	ft_one_quatition(char *str, int len)
// {
// 	int	i;
// 	int	j;
// }
int	ft_singl_quatition(char *str, int len)
{
	int	i;
	int	j;
	int	check;
	char *tmp;

	i = -1;
	check = 0;
	while (str[++i] && i < len)
	{
		if (str[i] == '\'' && ft_double_len(str, i) % 2 == 0)
		{
			j = i;
			while (str[++j] && j < len)
			{
				if (str[j] == '\'')
				{
					tmp = ft_substr(str, i, (i - j));
					printf("tmp_single->%s\n",str);
					check = 1;
					i = j;
				}
			if (ft_singl_helper(tmp, &check))
				return(1);
			}
		}
	}
	return (0);
}
int	ft_singl_helper(char *str, int *check)
{

	if (*check == 1)
	{
		printf("single_helper\n");
		if (ft_single_len(str, (int) ft_strlen(str)) % 2 != 0)
		{
			free(str);
			return(1);
		}
		else
		{
			free(str);
			*check = 0;
			return(0);
		}
	}
	return (0);
}
int	ft_single_len(char *str, int len)
{
	int	i;
	int	singl;

	singl = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'')
			singl++;
		i++;
	}
	return(singl);
}
