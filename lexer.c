/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:01 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/04 19:51:31 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ft_get_line(t_state *state)
{
	int	i;
	int	j;
	char **argv_line;
	char *line;

	i = 1;
	j = 0;
	line = ft_strtrim(state->line," ");
	argv_line = ft_split(line, ' ');
	state->lexer->command = argv_line[0];
	while (argv_line[i])
	{
		if (ft_flag_check(argv_line[i][0] == '-'))
		{

		}

	}
	// printf("%s\n",line);
}
