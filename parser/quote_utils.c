/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:54:48 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/03 16:16:52 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_cut_dquote(char *str, int *i, int *j, int len, int *check, int *sq)
{
	char *tmp;
	int	c;

	tmp = NULL;
	c = -1;
	while (str[++(*j)] && *j < len)
	{
		if ((str[*j] == '"' || str[(*j) + 1] == '\0') && *check == 0)
		{
			tmp = ft_substr(str, *i, (*j - *i) + 1);
			*check = 2;
			*i = *j;
			while (tmp[++c])
				if (tmp[c] == '\'')
					(*sq)++;
			break;
		}
	}
	return (tmp);
}
char *ft_cut_squote(char *str, int *i, int *j, int len, int *check, int *dq)
{
	char	*tmp;
	int		c;

	tmp = NULL;
	*j = *i;
	c = -1;
	while (str[++(*j)] && *j < len)
	{
		if ((str[*j] == '\'' ||  str[(*j)+1] == '\0') && *check == 0)
		{
			tmp = ft_substr(str, *i, (*j - *i) + 1);
			*check = 1;
			*i = *j;
			while (tmp[++c])
				if (tmp[c] == '"')
					(*dq)++;
			break;
		}
	}
	return(tmp);
}
int	ft_count_quote(char *str, int len, char quote_type)
{
	int	i;
	int	quote_len;

	quote_len = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == quote_type)
			quote_len++;
		i++;
	}
	return (quote_len);
}
