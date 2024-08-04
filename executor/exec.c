/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:59:43 by ekose             #+#    #+#             */
/*   Updated: 2024/08/04 20:27:38 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_cmd_get(t_state *state, t_cluster *cluster)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	if (cluster->cmd[0][0] == '/' || cluster->cmd[0][0] == '.')
	{
		return (NULL);
	}
	while (state->sep_path[i])
	{
		tmp = ft_strjoin(state->sep_path[i], "/");
		command = ft_strjoin(tmp, cluster->cmd[0]);
		free(tmp);
		if (access(command, X_OK) == 0)
			execve(command, cluster->cmd, state->envp);
		free (command);
		i++;
	}
	return (NULL);
}

static void	ft_open_pipes(t_state *state)
{
	int	**fd;
	int	i;

	i = -1;
	fd = (int **) malloc(sizeof(int *) * state->cmd_count);
	fd[state->cmd_count - 1] = NULL;
	while (++i < state->cmd_count - 1)
		fd[i] = malloc(sizeof(int) * 2);
	state->fd = fd;
	i = -1 ;
	while (++i < state->cmd_count - 1)
		pipe(state->fd[i]);
}

static void	ft_execve(t_state *state, t_cluster *cluster, int i, int check)
{
	char	*cmd_path;

	ft_dup_init(state, cluster, i, check);
	if (state->cmd_count > 1 && check > 0)
	{
		ft_route(state);
		exit(0);
	}
	cmd_path = ft_cmd_get(state, cluster);
	if (cmd_path == NULL)
		ft_executer_error(cluster->cmd, "command not found");
	exit(127);
}

void	ft_executer(t_state *state)
{
	t_cluster	*tmp;
	int			i;
	int			check;

	ft_open_pipes(state);
	tmp = state->cluster;
	i = 0;
	while (tmp)
	{
		check = ft_check_built(tmp);
		if (tmp->cmd)
		{
			if (check > 0 && state->cmd_count == 1)
				ft_route(state);
			else
			{
				tmp->pid = fork();
				if (tmp->pid == 0)
					ft_execve(state, tmp, i, check);
			}
			i++;
		}
		tmp = tmp->next;
	}
	ft_close_pipe(state, check);
}
