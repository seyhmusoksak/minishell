/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:11:13 by ekose             #+#    #+#             */
/*   Updated: 2024/08/15 13:07:35 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_built_exit_cmd(t_state *state, t_cluster *cluster)
{
	int	i;

	i = -1;
	if (cluster->cmd[1] != NULL)
	{
		while (cluster->cmd[1][++i])
		{
			if (ft_isdigit(cluster->cmd[1][i]) == 0
			&& (cluster->cmd[1][i] != '-' || i != 0))
			{
				ft_putstr_fd("exit\nminishell: exit: ", 2);
				ft_putstr_fd(cluster->cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				ft_full_free(state, 255);
			}
		}
		if (cluster->cmd[2] != NULL)
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			ft_full_free(state, 1);
		}
		ft_full_free(state, ft_atoi(cluster->cmd[1]));
	}
	ft_full_free(state, 0);
}
