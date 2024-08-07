/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/07 19:41:50 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// "ec"h"o" "me'm'o" 'na"s"im' yi"l"m'a'z "h"a"c"i 't'a'm'am""dir
void	ft_send_cleaner(t_parser *parser)
{
	parser->i = -1;
	parser->space = 0;
	while (parser->src[++parser->i])
	{
		parser->j = 0;
		ft_cleaner(parser, -1);
	}
}

void	ft_cleaner(t_parser *pars, int i)
{
	while (pars->src[pars->i][++i])
	{
		if (pars->src[pars->i][i] == ' ' && pars->space == 0
			&& ft_quote_check(pars->src[pars->i], i, pars) == 0)
		{
			pars->cleaned[pars->i][pars->j++] = pars->src[pars->i][i];
			while (pars->src[pars->i][i] == ' ')
				pars->space = i++;
			i--;
		}
		else
			ft_cleaner_helper(pars, &i);
	}
	pars->cleaned[pars->i][pars->j] = '\0';
}

void	ft_cleaner_helper(t_parser *prs, int *i)
{
	if (prs->space > 0
		&& (prs->src[prs->i][*i] == '"' && *i -1 >= 0
		&& ((prs->src[prs->i][*i -1] != '\0' && prs->src[prs->i][*i -1] == ' ')
		&& ft_quote_check(prs->src[prs->i], *i, prs) == 0))
		&& ft_is_first(prs->src[prs->i] + *i, '"', *i, prs) == 2)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'F', '"', prs);
	else if (prs->space > 0
		&& (prs->src[prs->i][*i] == '\'' && *i -1 >= 0
		&& ((prs->src[prs->i][*i -1] != '\0' && prs->src[prs->i][*i -1] == ' ')
		&& ft_quote_check(prs->src[prs->i], *i, prs) == 0))
		&& ft_is_first(prs->src[prs->i] + *i, '\'', *i, prs) == 1)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'F', '\'', prs);
	else if (prs->src[prs->i][*i] == '"'
		&& ft_quote_check(prs->src[prs->i], *i +1, prs) == 2)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'N', '"', prs);
	else if (prs->src[prs->i][*i] == '\''
		&& ft_quote_check(prs->src[prs->i], *i +1, prs) == 1)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'N', '\'', prs);
	else
		prs->cleaned[prs->i][prs->j++] = prs->src[prs->i][*i];
	return ;
}

int	ft_is_first(char *str, char keycode, int i, t_parser *pars)
{
	i = 0;
	if (keycode == '"')
	{
		while (str[++i])
		{
			if (((str[i +1] != '\0' && str[i +1] == ' ') || str[i +1] == '\0')
				&& ft_quote_check(str, i +1, pars) == 0 && str[i] == '"')
				return (2);
			else if (str[i] == ' ' && ft_quote_check(str, i, pars) == 0)
				break ;
		}
	}
	else if (keycode == '\'')
	{
		while (str[++i])
		{
			if (((str[i + 1] != '\0' && str[i +1] == ' ') || str[i +1] == '\0')
				&& ft_quote_check(str, i + 1, pars) == 0 && str[i] == '\'')
				return (1);
			else if (str[i] == ' ' && ft_quote_check(str, i, pars) == 0)
				break ;
		}
	}
	return (0);
}

int	ft_write_in_quote(char *str, char cod, char q, t_parser *prs)
{
	int	c;

	c = 0;
	if (cod == 'F')
		prs->cleaned[prs->i][prs->j++] = str[c];
	while (str[++c])
	{
		if (str[c] == ' ' && ft_quote_check(str, c, prs) == 0)
			return (--c);
		if (str[c] == q && ft_quote_check(str, c +1, prs) == 0
			&& cod != 'F')
			break ;
		if (str[c] != q)
			prs->cleaned[prs->i][prs->j++] = str[c];
		else if ((str[c] == q && ((str[c +1] && str[c +1] == ' ') || !str[c +1])
				&& !ft_quote_check(str, c +1, prs)) && cod == 'F' && prs->space)
		{
			prs->cleaned[prs->i][prs->j++] = str[c];
			prs->space = 0;
			break ;
		}
	}
	return (c);
}

