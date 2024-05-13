/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/12 18:20:05 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_str(char *str, char *clean_str)
{
	int	i;
	int	check_space;

	check_space = 0;
	i = -1;
	while (str[i])
	{
		if ((str[i] != '"' && str[i] != '\'')
			|| (check_space == 1 && (str[i] == '\'' || str[i] == '"')))
		{
			clean_str[i] = str[i];
			check_space = 0;
		}
		if (str[i] == ' ' && ft_qutation_len_check(str, i) == 0)
		{
			check_space = 1;
			while (str[i + 1] && str[i + 1] == ' ')
				i++;
		}
		if (((str[i] == '\'' || str[i] == '"') && ((str[i + 1] == '\0') || (str[i + 1] != '\0' && str[i + 1] == ' ')) && ft_qutation_len_check(str, i)))
				clean_str[i] = str[i];
		i++;
	}
}
int ft_qutation_check(char *str)
{
	int	i;
	int singl;
	int dbl;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			singl++;
			if (dbl % 2 != 0)
				return (1);
		}
		else if (str[i] == '\"')
			dbl++;
		i++;
	}
	if (singl % 2 != 0 || dbl % 2 != 0)
		return(1);
	return (0);
}

int ft_qutation_len_check(char *str, int len)
{
	int	i;
	int singl;
	int dbl;

	i = 0;
	while (i < len)
	{
		if (str[i] == '\'')
		{
			singl++;
			if (dbl % 2 != 0)
				return (1);
		}
		else if (str[i] == '\"')
			dbl++;
		i++;
	}
	if (singl % 2 != 0 || dbl % 2 != 0)
		return(1);
	return (0);
}
