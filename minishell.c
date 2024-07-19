/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soksak <soksak@42istanbul.com.tr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:02 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/19 05:29:05 by soksak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	main(int argc, char **argv, char **envp)
{
	t_state	*state;
	// t_env	*tmp;
	// int		i;
	// i = 0;
	state = (t_state *)malloc(sizeof(t_state));
	state->pars = malloc(sizeof(t_parser));
	// if (!state->pars || !state->lexer || !state)
	// 	ft_error_mesage("Error: Malloc problem !");
	(void)argc;
	(void)argv;
	state->pars->exit_check = 0;
	state->env = get_env(state, envp);
	state->pars->env = state->env;

	// tmp = state->env;
	// while (tmp != NULL)
	// {
	// 	printf("Key: %s\n", tmp->key);
	// 	printf("Value: %s\n", tmp->value);
	// 	tmp = tmp->next;
	// }
	// printf("pid : %d\n", getpid());
	while (1)
	{
		state->line = readline("minishell>");
		if (ft_parser(state))
			break ;
		state->lexer = add_lexer_node(state);
		int a = 0;
		while (state->lexer[a] != NULL)
		{

				printf("pipe = %d\n", a);
				printf("-------------------------\n");
			while (state->lexer[a])
			{
				printf("command: %s\n", state->lexer[a]->command);
				printf("type: %d\n", state->lexer[a]->type);
				state->lexer[a] = state->lexer[a]->next;
			}
				printf("-------------------------\n");
			a++;
		}
		my_lexer_free(state->lexer);
		ft_free_thrd_str(state->clean_thrd_argv);
	}
	ft_full_free(state);
	return (0);
}
