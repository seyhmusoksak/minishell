/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/10 02:34:59 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arg_check(char *str)
{
	int	i;

	i = -1;
	if (ft_qutation_check(str))
		return (1);
	while (str[i])
	{
		while (str[i] != '|' && str[i] != ' ')
			i++;
			// burayı duşunuyorum sabah bakcam
		while (str[i] == ' ')
				i++;
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
		{
			dbl++;
			if (singl % 2 != 0)
				return (1);
		}
		i++;
	}
	if (singl % 2 != 0 || dbl % 2 != 0)
		return(1);
	return (0);
}
