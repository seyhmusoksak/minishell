/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:08:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/02 17:39:41 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_mesage(char *str)
{
	char	*red_color;
	char	*reset_color;

	red_color = "\033[1;31m";
	reset_color = "\033[0m";
	write(2, red_color, ft_strlen(red_color));
	write(2, str, ft_strlen(str));
	write(2, reset_color, ft_strlen(reset_color));
	write(2, "\n", 1);

	return (1);
}

void	ft_clean_env(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp2->key);
		free(tmp2->value);
		tmp = tmp->next;
		free(tmp2);
	}
}

int	ft_full_free(t_state *state)
{
	ft_clean_env(&state->env);
	free(state->pars);
	free(state->lexer);
	free(state);
	return (1);
}

int	ft_exit(char *line, char *msg)
{
	free(line);
	ft_error_mesage(msg);
	return (0);
}
