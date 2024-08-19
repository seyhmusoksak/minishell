/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:56:39 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/15 13:09:35 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_wordlen(char *s, char c, int j, t_parser *parser)
{
	int	i;

	i = 0;
	while (s[j]
		&& (s[j] != c || (s[j] == c && ft_quote_check(s, j, parser))))
	{
		j++;
		i++;
	}
	return (i);
}

static char	*ft_write(char *s, char c, int start, t_parser *parser)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = start;
	dest = malloc(sizeof(char) * (ft_wordlen(s, c, start, parser) + 1));
	if (!dest)
		return (0);
	while (s[i] && (s[i] != c || (s[i] == c && ft_quote_check(s, i, parser))))
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	**ft_pipe_split(char *s, char c, t_parser *pars)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = -1;
	if (!s)
		return (0);
	dest = malloc(sizeof(char *) * (ft_count_real_char(s, c, pars) + 2));
	if (!dest)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c && !ft_quote_check(s, i, pars))
			i++;
		if (s[i] != '\0')
			dest[++j] = ft_write(s, c, i, pars);
		while (s[i] && (s[i] != c || (s[i] == c && ft_quote_check(s, i, pars))))
			i++;
	}
	dest[++j] = NULL;
	return (dest);
}

int	ft_pipe_check(char *line, t_parser *parser)
{
	int		i;
	int		start;
	char	*sub;

	i = -1;
	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
		return (1);
	while (line[++i])
	{
		if (line[i] == '|' && !ft_quote_check(line, i, parser))
		{
			start = i +1;
			while (line[i] && (line[i] == '|' || line[i] == ' '))
				i++;
			sub = ft_substr(line, start, i - start);
			if (ft_strchr(sub, '|'))
			{
				free(sub);
				return (1);
			}
			else
				free(sub);
		}
	}
	return (0);
}
