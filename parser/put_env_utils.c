/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:54:53 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/28 14:16:45 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pars_str(char *s, t_parser *prs)
{
	if (prs->dolar_is_first)
	{
		prs->len_dolar[0] = prs->d +1;
		while (s[prs->d] != '\0' && s[prs->d] != ' ')
			prs->d++;
		prs->len_dolar[1] = prs->d -1;
		if (s[prs->d] != ' ' && prs->d >= (int)(ft_strlen(s) - 1))
		{
			prs->len_str[0] = -1;
			return ;
		}
		prs->len_str[0] = prs->d;
		while ((s[prs->d] && s[prs->d] != '$'))
			prs->d++;
		if (s[prs->d] == '$' && !ft_isdolr(s, prs->d, prs))
		{
			prs->d++;
			while ((s[prs->d] && s[prs->d] == '$' && !ft_isdolr(s, prs->d, prs))
				|| (s[prs->d] && s[prs->d] != '$'))
				prs->d++;
		}
		prs->len_str[1] = prs->d -1;
	}
	else
		ft_pars_str_helper(s, prs);
}

void	ft_pars_str_helper(char *s, t_parser *prs)
{
	prs->len_str[0] = prs->d;
	while ((s[prs->d] && s[prs->d] != '$'))
		prs->d++;
	if (s[prs->d] == '$' && !ft_isdolr(s, prs->d, prs))
	{
		prs->d++;
		while ((s[prs->d] && s[prs->d] != '$')
			|| (s[prs->d] && s[prs->d] == '$' && !ft_isdolr(s, prs->d, prs)))
			prs->d++;
	}
	prs->len_str[1] = prs->d -1;
	if (s[prs->d] != ' ' && prs->d >= (int)(ft_strlen(s) -1))
	{
		prs->len_dolar[0] = -1;
		return ;
	}
	prs->len_dolar[0] = prs->d +1;
	while (s[prs->d] != '\0' && s[prs->d] != ' ')
		prs->d++;
	prs->len_dolar[1] = prs->d -1;
}

int	ft_check_after_key(char *key)
{
	int		i;
	int		check_isalnum;

	check_isalnum = 0;
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i])
			&& key[i] != '<' && key[i] != '>' && key[i] != '_')
		{
			check_isalnum = 1;
			break ;
		}
		i++;
	}
	if (check_isalnum)
		return (i);
	return (0);
}

int	ft_check_is_in(char *str, int index, t_parser *parser)
{
	char	*sub;

	sub = ft_substr(str, 0, index);
	if (ft_quote_check(sub, index, parser) == 2)
	{
		free(sub);
		sub = NULL;
		return (1);
	}
	free(sub);
	sub = NULL;
	return (0);
}

int	ft_check_special(char *str, int i)
{
	if (str[i + 1] != '%' && str[i +1] != '+' && str[i +1] != ','
		&& str[i +1] != '/' && str[i +1] != ':' && str[i +1] != '='
		&& str[i +1] != ']' && str[i +1] != '^'
		&& str[i +1] != '}' && str[i +1] != '~')
		return (1);
	return (0);
}

