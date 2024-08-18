/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:43:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/18 14:12:24 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_last_redirect(t_parser *parser)
{
	int		i;
	char	*trim;

	i = -1;
	while (parser->cleaned[++i])
	{
		trim = ft_strtrim(parser->cleaned[i], " ");
		if (trim[ft_strlen(trim) - 1] == '>'
			|| trim[ft_strlen(trim) - 1] == '<')
		{
			free(trim);
			return (1);
		}
		free(trim);
	}
	return (0);
}

static int	ft_check_redirect(char **split, int i, int result)
{
	while (++i < ft_double_str_len(split) - 1)
	{
		if (split[i +1]
			&& !ft_check_full_char(split[i +1], ' ', ft_strlen(split[i +1])))
		{
			result = 1;
			break ;
		}
		else if (split[i +1] && !ft_check_redirect_char(split[i +1]))
		{
			result = 1;
			break ;
		}
		else if (split[i +1] == NULL)
		{
			result = 1;
			break ;
		}
	}
	ft_free_double_str(split);
	if (result)
		return (1);
	return (0);
}

int	ft_redirection_control(t_parser *parser, int i)
{
	int		check;

	check = -1;
	if (ft_check_last_redirect(parser))
		return (1);
	while (parser->cleaned[++i])
	{
		if (ft_count_real_char(parser->cleaned[i], '>', parser)
			|| ft_count_real_char(parser->cleaned[i], '<', parser))
		{
			check = 0;
			break ;
		}
	}
	i = -1;
	while (parser->cleaned[++i] && check == 0)
		check = ft_check_redirect(
				ft_pipe_split(parser->cleaned[i], '>', parser), -1, 0);
	i = -1;
	while (parser->cleaned[++i] && check == 0)
		check = ft_check_redirect(
				ft_pipe_split(parser->cleaned[i], '>', parser), -1, 0);
	if (check == 0 || check == -1)
		return (0);
	return (1);
}

int	ft_check_full_char(char *str, char c, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int	r(t_parser *parser, char r, char l)
{
	parser->one = -1;
	while (parser->cleaned[++parser->one])
	{
		parser->two = -1;
		while (parser->cleaned[parser->one][++parser->two])
		{
			if (parser->cleaned[parser->one][parser->two] == l
			&& ft_quote_check(parser->cleaned[parser->one],
				parser->two, parser) == 0)
			{
				if (ft_control_red(parser, r, l) == 1)
					return (1);
			}
			else if (parser->cleaned[parser->one][parser->two] == r
			&& ft_quote_check(parser->cleaned[parser->one],
				parser->two, parser) == 0)
			{
				if (ft_control_red(parser, l, r) == 1)
					return (1);
			}
		}
	}
	return (0);
}









// 			&& parser->cleaned[i][j + 1] == '>' )|| (parser->cleaned[i][j] == '<') && !ft_quote_check(parser->cleaned[i], j, parser))
// 				return (1);
// 			j++;
// 		}
// 		{
// 			/* code */
// 		}


// 	}
// 	{
// 		if (str[i] == '>')
// 			return (1);
// 		if (str[i] == '<')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
