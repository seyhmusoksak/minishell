/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:05:15 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/14 15:25:04 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	ft_signal_handler(int sig)
{
	(void)sig;
	if (g_sig_status == IN_CAT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
	}
	else if (g_sig_status == IN_HERADOC)
	{
		write (1, "\n", 1);
		exit(1);
	}
	else if (g_sig_status == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sig_status = 0;
}

void	ft_init_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
