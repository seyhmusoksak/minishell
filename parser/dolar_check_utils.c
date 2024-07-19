/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:58:11 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/15 21:48:57 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_dolar(char *str, t_parser *parser)
{
	int	i;
	int	count_dolar;

	count_dolar = 0;
	if (ft_strchr(str, '$') != NULL && ft_strlen(str) > 1)
	{
		i = 0;
		while (str[i])
		{
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' && str[i +1] && str[i +1] != ' '
				&& str[i +1] != '\'' && str[i +1] != '"'
				&& ft_quote_check(str + i, ft_strlen(str), parser) != 1)
				count_dolar++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		if (ft_last_is_dolar(str, ft_strlen(str) - 1, 0, parser)
			|| ft_first_is_dolar(str) || count_dolar == 0)
			return (count_dolar);
		else
			return (count_dolar +1);
	}
	return (0);
}

int	ft_isdolr(char *str, int index, t_parser *parser)
{
	char	*check_str;
	int		start;

	if (str[index +1] != '\0' && str[index +1] != ' ' && str[index +1] != '"'
		&& str[index +1] != '\'' && ft_quote_check(str, index + 2, parser) != 1)
	{
		start = index;
		while (str[index] != ' ' && str[index])
			index++;
		check_str = ft_substr(str, start, index);
		if (ft_quote_check(check_str, index, parser) != 1)
		{
			free(check_str);
			check_str = NULL;
			return (1);
		}
		free(check_str);
		check_str = NULL;
	}
	return (0);
}

int	ft_last_is_dolar(char *str, int len, int i, t_parser *parser)
{
	char	*tmp;

	(void)parser;
	i = len;
	if (ft_check_space(str, len, i) && str[len] == '"')
		return (1);
	if (str[i] == '"' && i -1 >= 0 && str[i -1] == ' ')
	{
		i--;
		while (i >= 0 && str[i] == ' ')
			i--;
	}
	else
		while (i >= 0 && str[i] != ' ')
			i--;
	tmp = ft_substr(str, i +1, len - i);
	if (ft_check_last(tmp))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	ft_check_last(char *tmp)
{
	if (tmp == NULL || !ft_strchr(tmp, '$') || ft_strchr(tmp, '\'')
		|| (tmp[0] == '$' && tmp[1] == '\0'))
		return (0);
	else if (tmp[0] == '$' && tmp[1]
		&& (tmp[1] == '"' || tmp[1] == ' ' || tmp[1] == '\''))
		return (0);
	return (1);
}

int	ft_first_is_dolar(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	tmp = ft_substr(str, 0, i);
	if (ft_strchr(tmp, '$'))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
