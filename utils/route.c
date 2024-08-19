/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:07:13 by ekose             #+#    #+#             */
/*   Updated: 2024/08/15 13:10:39 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_route(t_state *state, t_cluster *tmp)
{
	if ((tmp->cmd) == NULL)
		return ;
	else if (ft_strcmp(tmp->cmd[0], "exit") == 0
		&& tmp->pid != 0)
		ft_built_exit_cmd(state, tmp);
	else if (ft_strcmp(tmp->cmd[0], "cd") == 0)
		ft_cd(&state);
	else if (ft_strcmp(tmp->cmd[0], "pwd") == 0)
		ft_pwd(tmp, state);
	else if (ft_strcmp(tmp->cmd[0], "echo") == 0)
		ft_echo(tmp, state);
	else if (ft_strcmp(tmp->cmd[0], "export") == 0)
		ft_export_status(&state, tmp);
	else if ((ft_strcmp(tmp->cmd[0], "env") == 0
			|| ft_strcmp(tmp->cmd[0], "ENV") == 0))
		ft_print_env(state, tmp);
	else if (ft_strcmp(tmp->cmd[0], "unset") == 0)
		ft_del_env(&state, tmp);
}

int	ft_check_built(t_cluster *cluster)
{
	if ((cluster->cmd) == NULL)
		return (-1);
	else if (ft_strcmp(cluster->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cluster->cmd[0], "pwd") == 0)
		return (2);
	else if (ft_strcmp(cluster->cmd[0], "echo") == 0)
		return (3);
	else if (ft_strcmp(cluster->cmd[0], "export") == 0)
		return (4);
	else if (ft_strcmp(cluster->cmd[0], "env") == 0
		|| ft_strcmp(cluster->cmd[0], "ENV") == 0)
		return (5);
	else if (ft_strcmp(cluster->cmd[0], "unset") == 0)
		return (6);
	else if (ft_strcmp(cluster->cmd[0], "exit") == 0)
		return (7);
	return (-1);
}
