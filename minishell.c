/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/05/08 14:16:51 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	state->env = get_env(state, envp);
	state->lexer=malloc(sizeof(t_lexer));
	// state->lexer->command="ls";
	state->sep_path = ft_sep_path(state);

	while (1)
	{
		state->line = readline("minishell$ ");
		if (!state->line)
			break ;
		state->lexer = add_lexer_node(state->line);
		ft_exec(state);
		while (state->lexer)
		{
			printf("command: %s\n", state->lexer->command);
			printf("type: %d\n", state->lexer->type);
			state->lexer = state->lexer->next;
		}
	}
	(void)argc;
	(void)argv;

	return (0);

}
