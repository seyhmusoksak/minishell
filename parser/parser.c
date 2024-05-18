/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:02:28 by musozer           #+#    #+#             */
/*   Updated: 2024/05/18 14:14:42 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_error(char **str)
{
	free_split(str);
	printf("Error : Enter a value after the | sign \n");
}

int	ft_qutation_check(char *str)
{
	int	i;
	int	singl;
	int	dbl;

	i = 0;
	singl = 0;
	dbl = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			singl++;
			if (dbl % 2 != 0)
				return (1);
		}
		else if (str[i] == '\"')
			dbl++;
		i++;
	}
	if (singl % 2 != 0 || dbl % 2 != 0)
		return (1);
	return (0);
}

char	**pipe_join(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(str[i], "|");
	free(str[i]);
	str[i] = tmp;
	tmp = NULL;
	tmp = ft_strjoin(str[i], str[i + 1]);
	free(str[i]);
	free(str[i + 1]);
	str[i + 1] = NULL;
	str[i] = tmp;
	return (str);
}

char	**pipe_split(t_state *state)
{
	t_parser	*parser;
	int			i;
	char		**str;
	char		**tmp;

	i = 0;
	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	str = ft_split(state->line, '|');
	// if (str[1] == NULL)
	// 	pipe_error(str);
	while (str[i])
	{
		if (str[i + 1] && ft_qutation_check(str[i])
			&& ft_qutation_check(str[i + 1]))
		{
			tmp = pipe_join(str);
			str = NULL;
			str = tmp;
			free(tmp);
		}
		i++;
	}
	return (str);
}

