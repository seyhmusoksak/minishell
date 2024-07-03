/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/03 16:55:55 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// "ec"ho"" "me'"m"o" 'nas"i''m'
// 01234567890123456789012345678
// "ec"h"o" "me'm'o" 'na"s"im' yi"l"m'a'z "h"a"c"i 't'a'm'am""dir

void	ft_cleaner(t_parser *pars, int i)
{
	while (pars->src[pars->i][++i])
	{
		if (pars->src[pars->i][i] == ' ' && pars->cspace == 0
			&& ft_quote_check(pars->src[pars->i], i) == 0)
		{
			pars->cleaned[pars->i][pars->j++] = pars->src[pars->i][i];
			while (pars->src[pars->i][i] == ' ')
				pars->cspace = i++;
			i--;
		}
		else
			ft_cleaner_helper(pars, &i);
	}
	pars->cleaned[pars->i][pars->j] = '\0';
}

void	ft_cleaner_helper(t_parser *prs, int *i)
{
	if (prs->cspace > 0
		&& (prs->src[prs->i][*i] == '"'
		&& ((prs->src[prs->i][*i -1] != '\0' && prs->src[prs->i][*i -1] == ' ')
		&& ft_quote_check(prs->src[prs->i], *i) == 0))
		&& ft_is_first(prs->src[prs->i] + *i, '"', *i) == 2)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'F', '"', prs);
	else if (prs->cspace > 0
		&& (prs->src[prs->i][*i] == '\'' && (prs->src[prs->i][*i -1] == ' '
		&& ft_quote_check(prs->src[prs->i], *i) == 0))
		&& ft_is_first(prs->src[prs->i] + *i, '\'', *i) == 1)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'F', '\'', prs);
	else if (prs->src[prs->i][*i] == '"'
		&& ft_quote_check(prs->src[prs->i], *i +1) == 2)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'N', '"', prs);
	else if (prs->src[prs->i][*i] == '\''
		&& ft_quote_check(prs->src[prs->i], *i +1) == 1)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'N', '\'', prs);
	else
		prs->cleaned[prs->i][prs->j++] = prs->src[prs->i][*i];
}

void	ft_send_cleaner(t_parser *parser)
{
	parser->i = -1;
	parser->cspace = 0;

	while (parser->src[++parser->i])
	{
		parser->j = 0;
		ft_cleaner(parser, -1);
	}
}

int	ft_is_first(char *str, char keycode, int i)
{
	i = 0;
	while (str[++i])
	{
		if (keycode == '"')
		{
			if (str[i] == '"'
				&& ((str[i +1] != '\0' && str[i +1] == ' ') || !str[i +1])
				&& ft_quote_check(str, i + 1) == 0)
				return (2);
			else if (str[i] == ' ' && ft_quote_check(str, i) == 0)
				break ;
		}
		else if (keycode == '\'')
		{
			if (str[i] == '\''
				&& ((str[i +1] != '\0' && str[i +1] == ' ') || !str[i +1])
				&& ft_quote_check(str, i + 1) == 0)
				return (1);
			else if (str[i] == ' ' && ft_quote_check(str, i) == 0)
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
		if (str[c] == ' ' && ft_quote_check(str, c) == 0)
			return (--c);
		if (str[c] == q && ft_quote_check(str, c +1) == 0
			&& cod != 'F')
			break ;
		if (str[c] != q)
			prs->cleaned[prs->i][prs->j++] = str[c];
		else if ((str[c] == q && ((str[c +1] && str[c +1] == ' ') || !str[c +1])
				&& !ft_quote_check(str, c +1)) && cod == 'F' && prs->cspace > 0)
		{
			prs->cleaned[prs->i][prs->j++] = str[c];
			prs->cspace = 0;
			break ;
		}
	}
	return (c);
}

