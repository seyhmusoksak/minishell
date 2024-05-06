/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soksak <soksak@42istanbul.com.tr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/05/06 04:09:18 by soksak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	state->env = get_env(state, envp);
	while (1)
	{
		state->line = readline("minishell$ ");
		if (!state->line)
			break ;
		state->lexer = add_lexer_node(state->line);
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
