/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:15:57 by musozer           #+#    #+#             */
/*   Updated: 2024/05/11 18:27:48 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;
	int		i;
	char	**str;

	i = 0;
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
}
