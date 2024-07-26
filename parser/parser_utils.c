/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:13:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/26 18:46:57 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_pipe_split(char *line, char c, t_parser *parser)
{
	char	**src;
	char	**tmp;
	int		pc;

	parser->char_check = 1;
	pc = (pipe_c(line, c, parser) + 1);
	src = ft_split(line, c);
	tmp = (char **)malloc(sizeof(char *) * (pc + 1));
	if (!tmp)
		return (NULL);
	tmp[pc] = NULL;
	ft_quote_control(src, tmp, c, parser);
	ft_free_double_str(src);
	return (tmp);
}

void	ft_quote_control(char **src, char **tmp, char c, t_parser *parser)
{
	char		*dst;
	int			j;
	int			i;

	i = 0;
	j = 0;
	while (src[i] != NULL)
	{
		if (parser->char_check)
		{
			dst = ft_strdup(src[i]);
			parser->char_check = 0;
		}
		if (ft_quote_check(dst, ft_strlen(dst), parser) != 0)
			ft_strjoin_and_free(&dst, src[++i], c);
		if (ft_quote_check(dst, ft_strlen(dst), parser) == 0 && dst != NULL)
		{
			tmp[j] = ft_strdup(dst);
			parser->char_check = ++i;
			j++;
		}
		free(dst);
	}
	tmp[j] = NULL;
}

int	pipe_c(char *line, char c, t_parser *parser)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(line) && line[i] != '\0')
	{
		if (line[i] == c && ft_quote_check(line, i, parser) == 0)
			count++;
		else if (line[i] == c && ft_quote_check(line, i, parser) != 0)
		{
			while (line[++i])
			{
				if ((line[i] == c || line[i + 1] == '\0')
					&& ft_quote_check(line, i, parser) == 0)
				{
					count++;
					break ;
				}
			}
		}
		i++;
	}
	return (count);
}

void	ft_strjoin_and_free(char **dst, char *s2, char c)
{
	char	*result;
	char	*tmp;
	char	c_str[2];

	c_str[0] = c;
	c_str[1] = '\0';
	if (!*dst || !s2)
		return ;
	tmp = ft_strjoin(*dst, c_str);
	result = ft_strjoin(tmp, s2);
	free(tmp);
	free(*dst);
	*dst = NULL;
	*dst = ft_strdup(result);
	free(result);
	return ;
}

int	ft_wait_for_input(t_state *state)
{
	int	i;

	i = 0;
	while (state->line[i])
	{
		if ((state->line[i] != 10) && (state->line[i] != 32))
			return (1);
		i++;
	}
	return (0);
}
