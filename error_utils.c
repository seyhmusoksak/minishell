/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:08:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/31 20:01:52 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_mesage(char *str)
{
	write(2, str, ft_strlen(str));
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
		//free(tmp2->sep_path);
		tmp = tmp->next;
		free(tmp2);
	}
}

int	ft_full_free(t_state *state)
{
	if (!state->pars->exit_check)
		ft_free_double_str(state->pars->clean_argv);
	ft_clean_env(&state->env);
	free(state->pars);
	free(state->lexer);
	free(state);
	return (1);
}

int	ft_exit(char *line, char *msg, t_parser *parser)
{
	free(line);
	ft_error_mesage(msg);
	parser->exit_check = 1;
	return (0);
}
