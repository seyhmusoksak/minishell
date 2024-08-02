/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:20:17 by ekose             #+#    #+#             */
/*   Updated: 2024/08/02 17:27:24 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_int_free(t_state *state)
{
	int	i;

	i = 0;
	if (state->fd)
	{
		while (state->fd[i])
		{
			free(state->fd[i]);
			i++;
		}
		free(state->fd);
	}
}

void	ft_wait(t_state *state, int check)
{
	t_cluster	*tmp;
	int			result;

	tmp = state->cluster;
	while (tmp)
	{
		waitpid(tmp->pid, &result, 0);
		if (!(check > 0))
			state->error = result >> 8;
		tmp = tmp->next;
	}
	ft_int_free(state);
}

void	ft_close_pipe(t_state *state, int check)
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
	ft_wait(state, check);
}

void	ft_pipe_connect(t_state *state, t_cluster *cluster, int i, int check)
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
	ft_close_pipe(state, check);
}

void	ft_dup_init(t_state *state, t_cluster *cluster, int i, int check)
{
	if (state->cmd_count > 1 && ft_strcmp(state->cluster->cmd[0], "exit"))
	{
		ft_pipe_connect(state, cluster, i, check);
	}
	if (cluster->files->fd_output >= 2)
		dup2(cluster->files->fd_output, STDOUT_FILENO);
	if (cluster->files->fd_input >= 2)
		dup2(cluster->files->fd_input, STDIN_FILENO);
}
