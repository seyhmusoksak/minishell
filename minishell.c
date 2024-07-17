/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:02 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/17 18:32:28 by musozer          ###   ########.fr       */
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
	state->lexer = malloc(sizeof(t_lexer));
	state->pars = malloc(sizeof(t_parser));
	if (!state->pars || !state->lexer || !state)
		ft_error_mesage("Error: Malloc problem !");
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
	}
	ft_full_free(state);
	return (0);
}
