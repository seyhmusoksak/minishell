/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/05/04 16:13:12 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;
	int		i;

	i = 0;
	state = (t_state *)malloc(sizeof(t_state));
	state->env = get_env(state, envp);
	(void)argc;
	(void)argv;
	state->lexer =malloc(sizeof(t_lexer));
	state->lexer->command = "pwd";
	state->sep_path= ft_sep_path(state);
	ft_exec(state);
	return (0);
}
