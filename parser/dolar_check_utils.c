/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:58:11 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/06 18:09:21 by mehmyilm         ###   ########.fr       */
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
			if (str[i] == '$' && ft_isdolr(str, i, parser))
				count_dolar++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count_dolar);
}

int	ft_isdolr(char *str, int i, t_parser *parser)
{
	char	*check_str;
	int		dval;
	int		sval;
	int		start;

	if (str[i] == '$' && str[i +1] != '\0' && str[i +1] != ' '
		&& str[i +1] != '"' && str[i +1] != '\''
		&& str[ft_strlen(str)- 1] != '\'' && ft_check_special(str[i +1]))
	{
		start = i;
		while (str[i] != ' ' && str[i])
			i++;
		check_str = ft_substr(str, start, (i - start));
		dval = ft_count_quote(check_str, i - start, '"') % 2;
		sval = ft_count_quote(check_str, i - start, '\'') % 2;
		if ((dval && sval) || (!dval && !sval) || (dval && !sval)
			|| (sval && ft_check_is_in(str, i, parser)))
		{
			free(check_str);
			return (1);
		}
		free(check_str);
	}
	return (0);
}

