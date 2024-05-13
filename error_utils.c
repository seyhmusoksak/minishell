/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:08:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/12 18:20:27 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_mesage(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], ft_strlen(str));
	write(2, "\n", 1);
	return(1);
}
int	ft_full_free(t_state *state)
{
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
