/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:43:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/07 20:43:45 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirection_control(t_parser *parser)
{
	parser->one = -1;
	parser->two = -1;

	if (ft_sign_in(parser, '<') || ft_sign_in(parser, '>')
		|| ft_redirection_in(parser, '>', '<')
		|| ft_redirection_in(parser, '<', '>')
		|| ft_new_redirection(parser, '<', '>', 0)
		|| ft_new_redirection(parser, '>', '<', 0))
		return (1);
	return (0);
}

int	ft_sign_in(t_parser *parser, char c)
{
	int	sign_in;

	sign_in = -1;
	parser->one = -1;
	while (parser->cleaned[++parser->one])
	{
		parser->two = -1;
		while (parser->cleaned[parser->one][++parser->two])
		{
			if ((parser->cleaned[parser->one][parser->two] == c
				&& ft_quote_check(parser->cleaned[parser->one],
					parser->two, parser) == 0)
				&& (++sign_in < 2))
			{
				if (parser->cleaned[parser->one][parser->two + 1] == '\0')
					return (1);
				else if (parser->cleaned[parser->one][parser->two + 1] != c)
					break ;
			}
			else if (sign_in == 2)
				return (1);
		}
	}
	return (0);
}

int	ft_redirection_in(t_parser *parser, char c, char d)
{
	parser->one = -1;
	while (parser->cleaned[++parser->one])
	{
		parser->two = -1;
		while (parser->cleaned[parser->one][++parser->two])
		{
			if (parser->cleaned[parser->one][parser->two] == c
			&& ft_quote_check(parser->cleaned[parser->one],
				parser->two, parser) == 0)
			{
				while (parser->cleaned[parser->one][++parser->two])
				{
					if (parser->cleaned[parser->one][parser->two] == ' '
					|| parser->cleaned[parser->one][parser->two] == '\t')
						continue ;
					else if (parser->cleaned[parser->one][parser->two] == d)
						return (1);
					else
						return (0);
				}
			}
		}
	}
	return (0);
}

int	ft_new_redirection(t_parser *parser, char c, char d, int k)
{
	parser->one = -1;
	while (parser->cleaned[++parser->one])
	{
		parser->two = -1;
		parser->red = 0;
		while (parser->cleaned[parser->one][++parser->two])
		{
			if (parser->cleaned[parser->one][parser->two] == c
				&&parser->cleaned[parser->one][parser->two + 1] == c)
				parser->two++;
			if (parser->cleaned[parser->one][parser->two] == c
			&& ft_quote_check(parser->cleaned[parser->one],
			parser->two, parser) == 0)
			{
				k = ft_redirect(parser, k, c, d);
				if (k == 0)
					return (1);
			}
		}
	}
	if (k == 1 || parser->red == 0)
		return (0);
	return (1);
}

int	ft_redirect(t_parser *parser, int k, char c, char d)
{
	char	a;

	parser->red = 1;
	while (parser->cleaned[parser->one][++parser->two])
	{
		a = parser->cleaned[parser->one][parser->two];
		if (a == ' ' || a == '\t')
			continue ;
		else if ((a == c || a == d) && k == 1)
		{
			k = 0;
			if (parser->cleaned[parser->one][parser->two + 1] == c
				|| parser->cleaned[parser->one][parser->two + 1] == d)
				parser->two++;
		}
		else if ((a == c || a == d) && k != 1)
			return (k);
		else
			k = 1;
	}
	parser->two--;
	return (k);
}
