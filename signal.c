/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:05:15 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/06 19:40:26 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	ft_signal_handler(int sig)
{
	(void)sig;
	if (sig_status == IN_CAT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		sig_status = 0;
	}
	else if (sig_status == IN_HERADOC)
	{
		write (1, "\n", 1);
		exit(0);
	}
	else if (sig_status == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	sig_status = 0;
}

void	ft_init_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
