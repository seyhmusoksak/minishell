/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:54:48 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/06/03 17:12:10 by mehmyilm         ###   ########.fr       */
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

int ft_dquote_len(char *str, int len)
{
	int i;
	int dbl;

	dbl = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '"')
			dbl++;
		i++;
	}
	return (dbl);
}
int	ft_squote_len(char *str, int len)
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
