/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/08/01 20:18:04 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	main(int argc, char **argv, char **envp)
{
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	state->lexer = malloc(sizeof(t_lexer));
	state->pars = malloc(sizeof(t_parser));
	if (!state->pars || !state->lexer || !state)
		ft_error_mesage("Error: Malloc problem !");
	(void)argc;
	(void)argv;
	sig_status = 0;
	state->pars->exit_check = 0;
	state->env = get_env(state, envp);
	state->exp = get_env(state, envp);
	ft_init_signals();
	while (1)
	{
		state->line = readline("minishell>");
		if (state->line)
			add_history(state->line);
		if (sig_status)
		{
			sig_status = 0;
			continue ;
		}
		ft_parser(state);
	}
	ft_full_free(state);
	return (0);
}

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("kardes kontrol c yapmaaaa !", 0);
		rl_redisplay();
	}
}
void	ft_init_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	// signal(SIGQUIT, SIG_IGN);
}

