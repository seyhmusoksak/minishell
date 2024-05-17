/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:08:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/18 01:27:44 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_mesage(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return(1);
}
int	ft_full_free(t_state *state)
{
	if (state->clean_argv != NULL)
		ft_free_double_str(state->clean_argv);
	free(state->pars);
	free(state->lexer);
	free(state->env);
	free(state);
	return(1);
}

void	ft_free_double_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
