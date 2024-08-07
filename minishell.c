/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:51:35 by soksak            #+#    #+#             */
/*   Updated: 2024/08/07 15:43:29 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

///export düzeltilecek	heredoc komutsuz düzeltilecek exec envsiz düzeltilecek
#include "minishell.h"

static void	ft_init_program(int argc, char **argv, char **envp, t_state **state)
{
	(void)argc;
	(void)argv;
	*state = (t_state *)malloc(sizeof(t_state));
	(*state)->pars = malloc(sizeof(t_parser));
	if (!(*state)->pars || !(*state))
		ft_error_mesage("Error: Malloc problem !");
	sig_status = 0;
	ft_init_signals();
	(*state)->env = get_env(*state, envp);
	(*state)->exp = (*state)->env;
	(*state)->envp = envp;
	(*state)->error = 0;
	(*state)->cluster = NULL;

}

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;

	ft_init_program(argc, argv, envp, &state);
	while (1)
	{
		ft_sep_path(state);
		state->pars->ptr_errno = &(state->error);
		state->line = readline("minishell>");
		if (state->line)
			add_history(state->line);
		if (ft_parser(state))
			break ;
		ft_free_double_str(state->sep_path);
		free(state->line);
		ft_all_cluster_free(state);
	}
	ft_full_free(state);
	return (0);
}



