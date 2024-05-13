/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:01 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/12 18:07:28 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_parser(t_state *state)
{
	char **argv;
	char	*line;
	line = ft_strtrim(state->line, " ");
	free(state->line);
	if (ft_qutation_check(line))
	{
		free(line);
		ft_error_mesage("Error: dquite hatasi");//mesaj duzenlenecek
		return(1);
	}
	argv = ft_pipe_split(line);
	ft_clean_quatition(argv);
	return (0);
}

char	**ft_pipe_split(char *line)
{
	int			i;
	char		**str;
	char		**tmp;

	i = 0;
	str = ft_split(line, '|');
	if (str[1] == NULL)
	{
		ft_free_double_str(str);
		ft_error_mesage("Error : Enter a value after the | sign");
	}
	while (str[i])
	{
		if (str[i + 1] && ft_qutation_check(str[i])
			&& ft_qutation_check(str[i + 1]))
		{
			tmp = ft_pipe_join(str);
			str = NULL;
			str = tmp;
			free(tmp);
		}
		i++;
	}
	return (str);
}
char	**ft_clean_quatition(char **str)
{
	int	i;
	int	len;
	char **trim_str;
	char **clean_str;

	i = -1;
	len = ft_double_str_len(str);
	trim_str = malloc(sizeof(char *) * len + 1);
	clean_str = malloc(sizeof(char *) * len + 1);
	if (!trim_str || !clean_str)
	{
		ft_error_mesage("Error: Malloc problem !");
		return(NULL);
	}
	while (str[++i])
		trim_str[i] = ft_strtrim(str[i], " ");
	trim_str[i + 1] = NULL;
	i = -1;
	while (trim_str[++i])
		ft_check_str(trim_str[i], clean_str[i]);
	clean_str[i + 1] = NULL;
	ft_free_double_str(str);
	ft_free_double_str(trim_str);
	return (clean_str);
}
