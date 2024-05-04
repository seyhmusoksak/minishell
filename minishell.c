/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/05/04 16:22:02 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/04 18:54:06 by mehmyilm         ###   ########.fr       */
=======
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/05/04 16:28:04 by mehmyilm         ###   ########.fr       */
>>>>>>> e16cfc873c7d32643a88187962323a259892faef
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
	state->lexer = malloc(sizeof(t_lexer));
	state->lexer->command = "pwd";
	state->sep_path= ft_sep_path(state);
	while (1)
	{
		state->line = readline("minishell>");
		ft_get_line(state);
	}
	ft_exec(state);
	return (0);
}
