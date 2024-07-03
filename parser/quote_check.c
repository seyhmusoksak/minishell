/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:29:21 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/03 16:20:53 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quote_check(char *str, int len)
{

	char	*tmp;
	char	*new_str;

	new_str = ft_substr(str,0,(size_t)len);
	tmp = NULL;
	if (ft_quote_handler(new_str, len,tmp,-1,0,0,0,0) == 1)
	{
		free(new_str);
		return(1);
	}
	else if (ft_quote_handler(new_str, len,tmp,-1,0,0,0,0) == 2)
	{
		free(new_str);
		return(2);
	}
	free(new_str);
	return (0);
}

int	ft_quote_handler(char *str, int len, char *tmp, int i, int j, int check, int sq, int dq)
{
	while (str[++i] && i < len)
	{
		if ((str[i] == '"' && str[i + 1] != '\0')  && ((ft_count_quote(str, i, '\'') - sq) % 2 == 0
			|| ((ft_count_quote(str,i, '"')) > 0 && (ft_count_quote(str, i, '"') - dq) % 2 == 0
			&& (ft_count_quote(str, i, '\'') - sq)% 2 != 0)) && check == 0)
		{
			j = i;
			tmp = ft_cut_dquote(str,&i, &j,len, &check,&sq);
		}
		else if ((str[i] == '\'' && str[i + 1] != '\0')  && ((ft_count_quote(str, i, '"') - dq) % 2 == 0
			|| ((ft_count_quote(str, i, '\'')) > 0 && (ft_count_quote(str, i, '\'') - sq) % 2 == 0
			&& (ft_count_quote(str, i, '"') - dq) % 2 != 0)) && check == 0)
			tmp = ft_cut_squote(str,&i, &j,len, &check, &dq);
		else if ((str[i] == '"' && (str[i + 1] == '\0' ||  (str[i + 1] != '\0' && str[i + 1] == ' ' )))
			&& (ft_count_quote(str,i + 1, '"') - dq)% 2 != 0)
			return(2);
		else if ((str[i] == '\'' && (str[i + 1] == '\0' ||  (str[i + 1] != '\0' && str[i + 1] == ' ' )))
			&& (ft_count_quote(str, i + 1, '\'') - sq) % 2 != 0)
			return(1);
		if(check == 2 && ft_quote_count_check(tmp, &check,dq, '"'))
			return(2);
		if (check == 1 && ft_quote_count_check(tmp, &check,sq, '\''))
			return(1);
	}
	return (0);
}

int ft_quote_count_check(char *str, int *check, int dq, char quote_type)
{
	(void) dq;
	if (*check == 2 && str != NULL)
	{
		if (ft_count_quote(str, (int)ft_strlen(str), quote_type) % 2 != 0)
		{
			free(str);
			return (1);
		}
		else
		{
			free(str);
			*check = 0;
			return (0);
		}
	}
	return (0);
}
