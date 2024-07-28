/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/07/28 21:15:11 by ekose            ###   ########.fr       */
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
	state->parser = malloc(sizeof(t_parser));
	// if (!state->pars || !state->lexer || !state)
	// 	ft_error_mesage("Error: Malloc problem !");
	(void)argc;
	(void)argv;
	state->parser->exit_check = 0;

	// printf("pid : %d\n", getpid());
	while (1)
	{
	state->env = get_env(state, envp);
	state->parser->env = state->env;
	// t_env *tmp;
	// tmp = state->env;
	// while (tmp != NULL)
	// {
	// 	printf("%s=%s\n", tmp->key,tmp->value);
	// 	// printf("Value %s\n", tmp->value);
	// 	tmp = tmp->next;
	// }
		state->line = readline("minishell>");
		if (ft_parser(state))
			break ;
		ft_cluster(state);
		ft_route(state);
	ft_clean_env(&state->env);
		// int i = 0;
		// t_cluster *head = state->cluster;
		// while(head)
		// {
		// 	i = 0;
		// 	printf("%s\n",head->cmd);
		// 	while(head->flag[i])
		// 		printf("flag->%s\n",head->flag[i++]);
		// 	i = 0;
		// 	while(head->arg[i])
		// 	{
		// 		printf("arg->%s\n",head->arg[i]);
		// 		i++;
		// 	}
		// 	if(*(head->files->input))
		// 		printf("input->%s\n",head->files->input);
		// 	if(*(head->files->output))
		// 		printf("output->%s\n",head->files->output);
		// 	printf("----------\n");
		// 	head = head->next;
		//}

		// ft_cluster_free(state);


		// state->lexer = add_lexer_node(state);
		// int a = 0;
		// while (state->lexer[a] != NULL)
		// {

		// 		printf("pipe = %d\n", a);
		// 		printf("-------------------------\n");
		// 	while (state->lexer[a])
		// 	{
		// 		printf("command: %s\n", state->lexer[a]->command);
		// 		printf("type: %d\n", state->lexer[a]->type);
		// 		state->lexer[a] = state->lexer[a]->next;
		// 	}
		// 		printf("-------------------------\n");
		// 	a++;
		// }
		// my_lexer_free(state->lexer);
		// ft_free_thrd_str(state->clean_thrd_argv);
	}
	// ft_full_free(state);
	return (0);
}
