/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:20:17 by ekose             #+#    #+#             */
/*   Updated: 2024/08/01 19:50:02 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_pipe(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->cmd_count -1)
	{
		if (state->fd[i][0])
			close(state->fd[i][0]);
		if (state->fd[i][1])
			close(state->fd[i][1]);
		i++;
	}
}

void	ft_pipe_connect(t_state *state, t_cluster *cluster, int i)
{
	if (state->cluster == cluster)
		dup2(state->fd[i][1], STDOUT_FILENO);
	else if (cluster->next == NULL)
		dup2(state->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(state->fd[i - 1][0], STDIN_FILENO);
		dup2(state->fd[i][1], STDOUT_FILENO);
	}
	ft_close_pipe(state);
}

void	ft_dup_init(t_state *state, t_cluster *cluster, int i)
{
	if (state->cmd_count > 1 && ft_strcmp(state->cluster->cmd[0], "exit"))
	{
		ft_pipe_connect(state, cluster, i);
	}
	if (cluster->files->fd_output >= 2)
		dup2(cluster->files->fd_output, STDOUT_FILENO);
	if (cluster->files->fd_input >= 2)
		dup2(cluster->files->fd_input, STDIN_FILENO);
}
