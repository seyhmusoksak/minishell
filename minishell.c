/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:02 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/10 01:13:13 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	main(int argc, char **argv, char **envp)
{
	t_state	*state;
	// int		i;
	// i = 0;
	state = (t_state *)malloc(sizeof(t_state));
	state->env = get_env(state, envp);
	state->lexer = malloc(sizeof(t_lexer));
	state->pars = malloc(sizeof(t_parser));
	(void)argc;
	(void)argv;
	if (!state->pars || !state->lexer || !state || !state->env)
			ft_error_0(state,"Error: Malloc problem !")
	state->lexer->command = "pwd";
	state->sep_path= ft_sep_path(state);
	while (1)
	{
		state->line = readline("minishell>");
		ft_parser(state);
	}
	ft_exec(state);
	return (0);
}
