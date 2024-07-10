/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:08:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/10 16:26:46 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_mesage(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

int	ft_full_free(t_state *state)
{
	if (!state->pars->exit_check)
		ft_free_double_str(state->clean_argv);
	free(state->pars);
	free(state->lexer);
	free(state->env);
	free(state);
	return (1);
}

void	ft_free_double_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}


int	ft_exit(char *line, char *msg, t_parser *parser)
{
	free(line);
	ft_error_mesage(msg);
	parser->exit_check = 1;
	return (1);
}
