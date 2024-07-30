/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:07:13 by ekose             #+#    #+#             */
/*   Updated: 2024/07/30 21:26:51 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_route(t_state *state)
{
	t_cluster	*tmp;

	/////enter gönderince leak var;
	tmp = state->cluster;
	while (tmp)
	{
		if ((tmp->cmd) == NULL)
			return ;
		else if (ft_strcmp(tmp->cmd[0], "cd") == 0)
			ft_cd(&state);
		else if (ft_strcmp(tmp->cmd[0], "pwd") == 0)
			ft_pwd(tmp);
		else if (ft_strcmp(tmp->cmd[0], "echo") == 0)
			ft_echo(tmp);
		else if (ft_strcmp(tmp->cmd[0], "export") == 0)
			ft_export_status(&state, tmp);
		else if (ft_strcmp(tmp->cmd[0], "env") == 0
			|| ft_strcmp(tmp->cmd[0], "ENV") == 0)
			ft_print_env(state);
		else if (ft_strcmp(tmp->cmd[0], "unset") == 0)
			ft_del_env(&state, tmp);
		tmp = tmp->next;
	}

}
