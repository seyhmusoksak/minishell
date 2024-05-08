/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:02 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/08 17:44:28 by mehmyilm         ###   ########.fr       */
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
	(void)argc;
	(void)argv;
	state->lexer = malloc(sizeof(t_lexer));
	state->pars = malloc(sizeof(t_parser));
	if (!state->pars || !state->lexer)
			exit(1); //Free eksik bakılması lazım
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
