/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/15 01:29:36 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//"e"c"h"o "memo" "n"a'"s'"i"m" > dequite hatası veriyor doğru sıkıntı yok
// "e"c"h"o "memo" "n"a"'s"i"m" ama burda tek tırnağı yazdırmıyor el at buna
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
	int dbl;

	i = 0;
	dbl = 2;
	if (ft_singl_quatition_check(str))
		return (1);
	while (str[i])
	{
		if (str[i] == '\"')
			dbl++;
		i++;
	}
	if (dbl % 2 != 0)
		return(1);
	return (0);
}
int	ft_singl_quatition_check(char *str)
{
	int	i;
	int	j;
	char *tmp;
	int check;

	check = 0;
	i = -1;
	while (str[++i])
	{
		if(str[i] == '\'')
		{
			j = i;
			while (str[++j])
			{
				if (str[j] == '\'')
				{
					tmp = ft_substr(str,i,(size_t) j);
					check = 1;
					i = j;
					break;
				}
			}
		}
		if(ft_singl_str_check(tmp, check))
			return(1);
	}
	return (0);
}
int ft_singl_str_check(char *singl_str, int check)
{
	if (check == 1)
	{
		if (ft_strchr(singl_str,'"'))
		{
			free(singl_str);
			return(1);
		}
		else
		{
			free(singl_str);
			check = 0;
			return(0);
		}
	}
	else
		return(0);
}
int ft_qutation_len_check(char *str, int len)
{
	int	i;
	int dbl;

	i = 0;
	dbl = 2;
	if (ft_singl_quatition_check(str))
		return (1);
	while (i <= len)
	{
		if (str[i] == '\"')
			dbl++;
		i++;
	}
	if (dbl % 2 != 0)
		return(1);
	return (0);
}
