/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/05/04 14:48:30 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	state->env = get_env(state, envp);
	(void)argc;
	(void)argv;
	// while(state->env)
	// {
	// 	if(ft_strncmp(state->env->key,"PATH",ft_strlen(state->env->key)) == 0)
	// 		printf("%s\n",state->env->value);

	// 	state->env= state->env->next;
	// }
	state->lexer->command = "ls";
	return (0);
}
