/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/06/03 17:13:44 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// "ec"ho"" "me'"m"o" 'nas"i''m'
// 01234567890123456789012345678
// "ec"h"o" "me'm'o" 'na"s"im' yi"l"m'a'z "h"a"c"i 't'a'm'am""dir
void	ft_clean_str(char *str, char *clean_str,int cspace, int i, int j)
{
	while (str[++i])
	{
		if (str[i] == ' ' && cspace == 0 && ft_quote_len_check(str, i) == 0)
		{
			clean_str[j++] = str[i];
 			while (str[i] == ' ')
 				cspace = i++;
			i--;
		}
		else if (cspace > 0 && (str[i] == '"' && ((str[i - 1] != '\0' && str[i - 1] == ' ')
			&& ft_quote_len_check(str, i) == 0))
		 && ft_is_first(str + i, '"', i) == 2)
			i+= ft_write_in_duble(str + i, clean_str, &j, &cspace,'F');
		else if (cspace > 0 && (str[i] == '\'' && (str[i - 1] == ' ' && ft_quote_len_check(str, i) == 0))
		&& ft_is_first(str + i, '\'', i) == 1)
			i+= ft_write_in_single(str + i, clean_str, &j, &cspace,'F');
		else if (str[i] == '"' && ft_quote_len_check(str, i + 1) == 2)
			i+= ft_write_in_duble(str + i, clean_str, &j, &cspace,'"');
		else if (str[i] == '\'' && ft_quote_len_check(str, i + 1) == 1)
			i+= ft_write_in_single(str + i, clean_str, &j, &cspace,'\'');
		else
			clean_str[j++] = str[i];
	}
	clean_str[j] = '\0';
}
int ft_is_first(char *str, char keycode, int i)
{
	i = 0;
	if (keycode == '"')
	{
		while (str[++i])
		{
			if ((str[i] == '"' && ((str[i + 1] != '\0' && str[i + 1] == ' ')
				|| str[i + 1] == '\0')) && ft_quote_len_check(str, i + 1) == 0)
				return (2);
			else if (str[i] == ' ' && ft_quote_len_check(str, i) == 0)
				break;
		}
	}
	else if (keycode == '\'')
	{
		while (str[++i])
		{
			if ((str[i] == '\'' && ((str[i + 1] != '\0' && str[i + 1] == ' ')
				|| str[i + 1] == '\0')) && ft_quote_len_check(str, i + 1) == 0)
				return (1);
			else if (str[i] == ' ' && ft_quote_len_check(str, i) == 0)
				break;
		}
	}
	return (0);
}
int ft_write_in_duble(char *str, char *clean_str, int *j, int *cspace, char keycode)
{
	int writed_char;

	writed_char = 0;
	if (keycode == 'F')
		clean_str[(*j)++] = str[writed_char];
	while (str[++writed_char])
	{
		// printf("in_double_j--> %d -->%c-->%d\n",*j,str[writed_char],writed_char);
		if ((str[writed_char] == ' ' && ft_quote_len_check(str, writed_char) == 0))
			return(--writed_char);
		if (str[writed_char] == '"' && ft_quote_len_check(str, writed_char + 1) == 0 && keycode != 'F')
			break ;
		if (str[writed_char] != '"')
			clean_str[(*j)++] = str[writed_char];
		else if (((str[writed_char] == '"' && ((str[writed_char + 1] != '\0'
			&& str[writed_char + 1] == ' ') || str[writed_char + 1] == '\0'))
			&& ft_quote_len_check(str, writed_char + 1) == 0) && keycode == 'F' && *cspace > 0)
		{
			clean_str[(*j)++] = str[writed_char];
			*cspace = 0;
			break ;
		}
	}
	return(writed_char);
}
int ft_write_in_single(char *str, char *clean_str, int *j, int *cspace, char keycode)
{
	int writed_char;

	writed_char = 0;
	if (keycode == 'F')
		clean_str[(*j)++] = str[writed_char];
	while (str[++writed_char])
	{
		// printf("in_single_j--> %d -->%c-->%d\n",*j,str[writed_char],writed_char);
		if (str[writed_char] == ' ' && ft_quote_len_check(str, writed_char) == 0)
			return(--writed_char);
		if (str[writed_char] == '\'' && ft_quote_len_check(str, writed_char + 1) == 0 && keycode != 'F')
			break ;
		if (str[writed_char] != '\'')
			clean_str[(*j)++] = str[writed_char];
		else if (((str[writed_char] == '\'' && ((str[writed_char + 1] != '\0'
			&& str[writed_char + 1] == ' ') || str[writed_char + 1] == '\0'))
			&& ft_quote_len_check(str, writed_char + 1) == 0) && keycode == 'F' && *cspace > 0)
		{
			clean_str[(*j)++] = str[writed_char];
			*cspace = 0;
			break;
		}
	}
	return (writed_char);
}

