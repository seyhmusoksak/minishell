/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:40:19 by musozer           #+#    #+#             */
/*   Updated: 2024/08/01 21:41:54 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_control(t_parser *parser)
{
	parser->one = -1;
	parser->two = 0;
	
	if (ft_sing_in(parser) == 1 || ft_sing_out(parser) == 1 || redirection_in(parser) == 1 || redirection_out(parser) == 1)
		return (1);
	return (0);
}

int	ft_sing_in(t_parser *parser)
{
	int	i;
	int	j;
	int	sing_in;

	sing_in = -1;
	i = -1;
	while (parser->cleaned[++i])
	{
		j = -1;
		while (parser->cleaned[i][++j])
		{
			if ((parser->cleaned[i][j] == '<'
				&& ft_quote_check(parser->cleaned[i], j, parser) == 0)
				&& (++sing_in < 2))
			{
				if (parser->cleaned[i][j + 1] == '\0')
					return (1);
				else if (parser->cleaned[i][j + 1] != '<')
					break ;
			}
			else if (sing_in == 2)
				return (1);
		}
	}
	return (0);
}

int	ft_sing_out(t_parser *parser)
{
	int	i;
	int	j;
	int	sing_out;

	sing_out = -1;
	i = -1;
	while (parser->cleaned[++i])
	{
		j = -1;
		while (parser->cleaned[i][++j])
		{
			if ((parser->cleaned[i][j] == '>'
				&& ft_quote_check(parser->cleaned[i], j, parser) == 0)
				&& (++sing_out < 2))
			{
				if (parser->cleaned[i][j + 1] == '\0')
					return (1);
				else if (parser->cleaned[i][j + 1] != '>')
					break ;
			}
			else if (sing_out == 2)
				return (1);
		}
	}
	return (0);
}

int redirection_in(t_parser *parser)
{
	parser->one = -1;
	parser->two = 0;
	while (parser->cleaned[++parser->one][parser->two])
	{
		parser->two = -1;
		while (parser->cleaned[parser->one][++parser->two])
		{
			if (parser->cleaned[parser->one][parser->two] == '<' && ft_quote_check(parser->cleaned[parser->one], parser->two, parser) == 0)  
			{
				while (parser->cleaned[parser->one][++parser->two])
				{
					if (parser->cleaned[parser->one][parser->two] == ' ' || parser->cleaned[parser->one][parser->two] == '\t')
						continue;
					else if (parser->cleaned[parser->one][parser->two] == '>')
						return (1);
					else	
						return (0);
				}
			}
		}
		
	}
	return (0);
}

int redirection_out(t_parser *parser)
{
	parser->one = -1;
	parser->two = 0;
	while (parser->cleaned[++parser->one][parser->two])
	{
		parser->two = -1;
		while (parser->cleaned[parser->one][++parser->two])
		{
			if (parser->cleaned[parser->one][parser->two] == '>' && ft_quote_check(parser->cleaned[parser->one], parser->two, parser) == 0)  
			{
				while (parser->cleaned[parser->one][++parser->two])
				{
					if (parser->cleaned[parser->one][parser->two] == ' ' || parser->cleaned[parser->one][parser->two] == '\t')
						continue;
					else if (parser->cleaned[parser->one][parser->two] == '<')
						return (1);
					else	
						return (0);
				}
			}
		}
		
	}
	return (0);
}
