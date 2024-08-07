/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:13:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/07 20:38:59 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_real_char(char *line, char c, t_parser *parser)
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

int	ft_wait_for_input(t_state *state)
{
	int	i;

	i = 0;
	if (!state->line)
		return (2);
	while (state->line[i])
	{
		if ((state->line[i] != 10) && (state->line[i] != 32))
			return (1);
		i++;
	}
	return (0);
}
char	*ft_resizer(char **str)
{
	char	*line;
	int		i;

	line = ft_strdup("");
	i = -1;
	while (str[++i])
		line = ft_strjoin(line, str[i]);
	ft_free_double_str(str);
	return (line);
}
