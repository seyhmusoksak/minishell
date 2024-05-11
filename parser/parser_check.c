/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/11 14:46:06 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arg_check(char *str)
{
	int	i;
	int j;

	j= 0;
	i = -1;
	if (ft_qutation_check(str))
		return (1);
	while (str[i])
	{
		while (str[i] != '|' && str[i] != ' ')
			i++;
		if (str[i] == ' ')
			while (str[i] == ' ')
				i++;
		if (str[i] == "")
		{

		}
		if (str[i] == '\'')
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
