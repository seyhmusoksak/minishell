/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soksak <soksak@42istanbul.com.tr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:15:57 by musozer           #+#    #+#             */
/*   Updated: 2024/05/13 15:38:06 by soksak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;
	int		i;
	//char	**str;

	i = 0;
	state = (t_state *)malloc(sizeof(t_state));
	state->lexer = (t_lexer **)malloc(sizeof(t_lexer *) * 5);
	state->env = get_env(state, envp);
	//char *str[] = {"echo -n", NULL};
	lexer_splitter(str, state);
	while (state->lexer[i])
	{
		while (state->lexer[i]->next)
		{
			printf("command: %s\n", state->lexer[i]->command);
			printf("type: %d\n", state->lexer[i]->type);
			state->lexer[i] = state->lexer[i]->next;
		}
		printf("--------------------\n");
		i++;
	}
	(void)argc;
	(void)argv;
}
