/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/14 00:38:59 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean_str(char *str, char *clean_str)
{
	ft_check_arg(str, clean_str, 0, 0, -1, 0);
}

void	ft_check_arg(char *str, char *clean_str, int fspace,int cspace, int i, int j)
{
	while (str[++i])
	{
		if ((str[i] != '"' && str[i] != '\'')
			|| (fspace > 0 && (str[i] == '\'' || str[i] == '"')))
		{
			clean_str[j++] = str[i];
			fspace = 0;
		}
		if (str[i] == ' ' && ft_qutation_len_check(str, i) == 0)
		{
			fspace =  cspace++;
			while (str[i + 1] && str[i + 1] == ' ')
				i++;
		}
		if (((str[i] == ' ') &&  (str[i + 1] != '\0' && ((str[i + 1] == '"')
			|| (str[i + 1] == '\''))) && ft_qutation_len_check(str, i + 1) )) //&& ft_last_quatiton_check(str,i)) eklenecek
				clean_str[j++] = str[++i];

		if ((((str[i] == '\'' || str[i] == '"') && (str[i + 1] == '\0'
			|| (str[i + 1] != '\0' && str[i + 1] == ' ')))
			&& ft_qutation_len_check(str, i) == 0) && cspace > 0)
			clean_str[j++] = str[i];
	}
	clean_str[j] = '\0';
}
// "e"c"h"o "memo" "n"a"s"im bu girdide yanlış çalışıyor  bunun için bu fonlsiyonu yazcam. daha bitmedi
// int	ft_last_quatiton_check(char *str , int start)
// {
// 	while (str[start] )
// 	{
// 		if ( (str[start] == '\'' || str[start] == '"')
// 			&& ((str[start + 1] != '\0' && str[start + 1] == ' ')
// 			|| (str[start] == '\0')))
// 			return(1);
// 		start++;
// 	}
// 	return(0);
// }
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
