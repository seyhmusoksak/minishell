/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:43:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/10 15:58:32 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

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

















// int	ft_sign_in(t_parser *parser, char c)
// {
// 	int	sign_in;

// 	sign_in = -1;
// 	parser->one = -1;
// 	while (parser->cleaned[++parser->one])
// 	{
// 		parser->two = -1;
// 		while (parser->cleaned[parser->one][++parser->two])
// 		{
// 			if ((parser->cleaned[parser->one][parser->two] == c
// 				&& ft_quote_check(parser->cleaned[parser->one],
// 					parser->two, parser) == 0)
// 				&& (++sign_in < 2))
// 			{
// 				if (parser->cleaned[parser->one][parser->two + 1] == '\0')
// 					return (1);
// 				else if (parser->cleaned[parser->one][parser->two + 1] != c)
// 					break ;
// 			}
// 			else if (sign_in == 2)
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

// int	ft_redirection_in(t_parser *parser, char c, char d)
// {
// 	parser->one = -1;
// 	while (parser->cleaned[++parser->one])
// 	{
// 		parser->two = -1;
// 		while (parser->cleaned[parser->one][++parser->two])
// 		{
// 			if (parser->cleaned[parser->one][parser->two] == c
// 			&& ft_quote_check(parser->cleaned[parser->one],
// 				parser->two, parser) == 0)
// 			{
// 				while (parser->cleaned[parser->one][++parser->two])
// 				{
// 					if (parser->cleaned[parser->one][parser->two] == ' '
// 					|| parser->cleaned[parser->one][parser->two] == '\t')
// 						continue ;
// 					else if (parser->cleaned[parser->one][parser->two] == d)
// 						return (1);
// 					else
// 						return (0);
// 				}
// 			}
// 		}
// 	}
// 	return (0);
// }

// int	ft_new_redirection(t_parser *parser, char c, char d, int k)
// {
// 	parser->one = -1;
// 	while (parser->cleaned[++parser->one])
// 	{
// 		parser->two = -1;
// 		parser->red = 0;
// 		while (parser->cleaned[parser->one][++parser->two])
// 		{
// 			printf("cleaned: %c\n", parser->cleaned[parser->one][parser->two]);
// 			if (parser->cleaned[parser->one][parser->two] == c
// 				&&parser->cleaned[parser->one][parser->two + 1] == c)
// 				parser->two++;
// 			if (parser->cleaned[parser->one][parser->two] == c
// 			&& ft_quote_check(parser->cleaned[parser->one],
// 			parser->two, parser) == 0)
// 			{
// 				k = ft_redirect(parser, k, c, d);  // 0 > <
// 				if (k == 0)
// 					return (1);
// 			}
// 		}
// 	}
// 	if (k == 1 || parser->red == 0)
// 		return (0);
// 	return (1);
// }

// int	ft_redirect(t_parser *parser, int k, char c, char d) // 0 > <
// {
// 	char	a;

// 	parser->red = 1;
// 	while (parser->cleaned[parser->one][++parser->two])
// 	{
// 		a = parser->cleaned[parser->one][parser->two];
// 		if (a == ' ' || a == '\t')
// 			continue ;
// 		else if ((a == c || a == d) && k == 1)
// 		{
// 			k = 0;
// 			if (parser->cleaned[parser->one][parser->two + 1] == c
// 				|| parser->cleaned[parser->one][parser->two + 1] == d)
// 				parser->two++;
// 		}
// 		else if ((a == c || a == d) && k != 1)
// 			return (k);
// 		else
// 			k = 1;
// 	}
// 	parser->two--;
// 	return (k);
// }
