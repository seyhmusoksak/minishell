/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:13:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/08 16:00:55 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_pipe_split(char *line, char c)
{
	char	**src;
	char	**tmp;
	int		pc;

	pc = (pipe_c(line, c) + 1);
	if (!line || (line[0] == c || line[ft_strlen(line) - 1] == c))
		return (NULL);
	src = ft_split(line, c);
	tmp = (char **)malloc(sizeof(char *) * (pc + 1));
	if (!tmp)
	{
		ft_free_double_str(src);
		return (NULL);
	}
	tmp[pc] = NULL;
	ft_quote_control(src, tmp, 0);
	ft_free_double_str(src);
	return (tmp);
}

void	ft_quote_control(char **src, char **tmp, int j)
{
	char	*dst;
	int 	check;
	int			i;

	i = 0;
	check = 1;
	while (src[i] != NULL)
	{
		if (check)
		{
			dst = ft_strdup(src[i]);
			check = 0;
		}
		if (ft_quote_len_check(dst, ft_strlen(dst)) != 0)
			ft_strjoin_and_free(&dst, src[++i]);
		if (ft_quote_len_check(dst, ft_strlen(dst)) == 0 && dst != NULL)
		{
			tmp[j] = ft_strdup(dst);
			check = 1;
			j++;
			i++;
		}
	}
	tmp[j] = NULL;
}

int	pipe_c(char *line, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(line) && line[i] != '\0')
	{
		if (line[i] == c && ft_quote_len_check(line, i) == 0)
			count++;
		else if (line[i] == c && ft_quote_len_check(line, i) != 0)
		{
			while (line[++i])
			{
				if ((line[i] == c || line[i + 1] == '\0')
					&& ft_quote_len_check(line, i) == 0)
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

void	ft_strjoin_and_free(char **dst, char *s2)
{
	char	*result;
	char	*tmp;

	if (!*dst || !s2)
		return ;
	tmp = ft_strjoin(*dst, "|");
	result = ft_strjoin(tmp, s2);
	free(tmp);
	free(*dst);
	*dst = NULL;
	*dst = ft_strdup(result);
	free(result);
	return ;
}
