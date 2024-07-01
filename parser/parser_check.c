/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/01 21:48:18 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// "ec"ho"" "me'"m"o" 'nas"i''m'
// 01234567890123456789012345678
// "ec"h"o" "me'm'o" 'na"s"im' yi"l"m'a'z "h"a"c"i 't'a'm'am""dir
void	ft_clean_str(char *str, char *clean_str, int cspace, int i, int j)
{
	while (str[++i])
	{
		if (str[i] == ' ' && cspace == 0 && ft_quote_len_check(str, i) == 0)
		{
			clean_str[j++] = str[i];
			while (str[i + 1] && str[i + 1] == ' ')
				cspace = i++;
		}
		else if (cspace > 0 && str[i] == '"' && str[i - 1] != '\0'
			&& str[i - 1] == ' ' && ft_quote_len_check(str, i) == 0
			&& ft_is_first(str + i, '"', 0) == 2)
			i += ft_write_in_quote(str + i, clean_str, &j, &cspace, 'F', '"');
		else if (cspace > 0 && str[i] == '\'' && str[i -1] == ' ' && ft_quote_len_check(str, i)
			&& ft_is_first(str + i, '\'', 0) == 1)
			i += ft_write_in_quote(str + i, clean_str, &j, &cspace, 'F', '\'');
		else if (str[i] == '"' && ft_quote_len_check(str, i + 1) == 2)
			i += ft_write_in_quote(str + i, clean_str, &j, &cspace, 'D' ,'"');
		else if (str[i] == '\'' && ft_quote_len_check(str, i + 1) == 1)
			i += ft_write_in_quote(str + i, clean_str, &j, &cspace, 'D', '\'');
		else
			clean_str[j++] = str[i];
	}
	clean_str[j] = '\0';
}
void	ft_cleaner(char *str, char *clean_str, t_parser *parser)
{
	parser->i = -1;
	parser->j = 0;
	parser->cspace = 0;
	parser->clean_str = clean_str;
	// ft_clean_str yi yazacam buraya
}
int	ft_is_first(char *str, char keycode, int i)
{
	if (keycode == '"')
	{
		while (str[++i])
		{
			if (((str[i +1] != '\0' && str[i +1] == ' ') || str[i +1] == '\0')
				&& ft_quote_len_check(str, i +1) == 0 && str[i] == '"')
				return (2);
			else if (str[i] == ' ' && ft_quote_len_check(str, i) == 0)
				break ;
		}
	}
	else if (keycode == '\'')
	{
		while (str[++i])
		{
			if (((str[i + 1] != '\0' && str[i +1] == ' ') || str[i +1] == '\0')
				&& ft_quote_len_check(str, i + 1) == 0 && str[i] == '\'')
				return (1);
			else if (str[i] == ' ' && ft_quote_len_check(str, i) == 0)
				break ;
		}
	}
	return (0);
}


int	ft_write_in_quote(char *str, char *clean_str, int *j, int *cspace, char keycode, char q)
{
	int	writed_char;

	writed_char = 0;
	if (keycode == 'F')
		clean_str[(*j)++] = str[writed_char];
	while (str[++writed_char])
	{
		if (str[writed_char] == ' ' && ft_quote_len_check(str, writed_char) == 0)
			return(--writed_char);
		if (str[writed_char] == q && ft_quote_len_check(str, writed_char +1) == 0 && keycode != 'F')
			break ;
		if (str[writed_char] != q)
			clean_str[(*j)++] = str[writed_char];
		else if (((str[writed_char] == q && ((str[writed_char + 1] != '\0'
			&& str[writed_char + 1] == ' ') || str[writed_char + 1] == '\0'))
			&& ft_quote_len_check(str, writed_char +1) == 0) && keycode == 'F' && *cspace > 0)
		{
			clean_str[(*j)++] = str[writed_char];
			*cspace = 0;
			break ;
		}
	}
	return (writed_char);
}

// void	ft_write_type(char *str, char *clean_str, int *j, int *cspace)
