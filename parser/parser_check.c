/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/14 23:01:20 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_clean_str(char *str, char *clean_str,int cspace, int i, int j)
{
	while (str[++i])
	{
		if ((str[i] != '"' && str[i] != '\'') )
			clean_str[j++] = str[i];
		if (str[i] == ' ' && ft_qutation_len_check(str, i) == 0)
		{
			cspace++;
			while (str[i + 1] && str[i + 1] == ' ')
				i++;
		}
		if (((str[i] == ' ') &&  (str[i + 1] != '\0' && ((str[i + 1] == '"')
			|| (str[i + 1] == '\''))) && ft_qutation_len_check(str, i + 1)
			&& ft_first_quatiton_check(str + i +1)))
				clean_str[j++] = str[++i];

		if ((((str[i] == '\'' || str[i] == '"') && ((str[i + 1] == '\0')
			|| (str[i + 1] != '\0' && str[i + 1] == ' ')))
			&& ft_qutation_len_check(str, i) == 0)
			&& cspace > 0 && ft_last_quatiton_check(str, i))
			clean_str[j++] = str[i];
	}
	clean_str[j] = '\0';
}
int	ft_first_quatiton_check(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if(ft_qutation_len_check(str, i) == 0 && ((str[i + 1] != '\0'
				&& str[i + 1] == ' ') || str[i + 1] == '\0'))
				return(1);
			else
				return(0);
		}
		else if (str[i] == '"')
		{
			if(ft_qutation_len_check(str, i) == 0 && ((str[i + 1] != '\0'
				&& str[i + 1] == ' ') || str[i + 1] == '\0'))
				return(1);
			else
				return(0);
		}
	}
	return(0);
}
int		ft_last_quatiton_check(char *str, int last)
{
	int	i;

	i = last - 1;
	while (i > 0)
	{
		if (str[i] == '\'')
		{
			if(ft_qutation_len_check(str, i) && (str[i -1] != '\0' && str[i - 1] == ' '))
				return(1);
			else
				return(0);
		}
		else if (str[i] == '"')
		{
			if(ft_qutation_len_check(str, i) && (str[i -1] != '\0' && str[i - 1] == ' '))
				return(1);
			else
				return(0);
		}
		i--;
	}
	return(0);
}
int ft_qutation_check(char *str)
{
	int	i;
	int singl;
	int dbl;

	i = 0;
	singl = 2;
	dbl = 2;
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
	singl = 2;
	dbl = 2;
	while (i <= len)
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
