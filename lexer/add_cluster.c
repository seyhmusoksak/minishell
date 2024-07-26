/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cluster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:11:58 by ekose             #+#    #+#             */
/*   Updated: 2024/07/26 17:06:21 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}





int	ft_open_input(t_state *state, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (ft_file_open_error(state, file));
	close(fd);
	return (0);
}

int	ft_open_output(t_state *state, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		return (ft_file_open_error(state, file));
	close(fd);
	return (0);
}
int	ft_args_add(t_state *state, char **cluster, t_cluster *structt)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	structt->files = (t_files *) malloc(sizeof(t_files));
	while (cluster[i])
	{
		if (i == 1)
		{
			structt->files->output = ft_strdup("");
			structt->files->input = ft_strdup("");
		}
		if (ft_strncmp(cluster[i], ">", 1) == 0)
		{
			free(structt->files->output);
			structt->files->output = ft_strdup(cluster[i + 1]);
			if (ft_open_output(state, structt->files->output) == -1)
				return (-1);
			i++;
		}
		else if (ft_strncmp(cluster[i], "<", 1) == 0)
		{
			free(structt->files->input);
			structt->files->input = ft_strdup(cluster[i + 1]);
			if (ft_open_input(state, structt->files->input) == -1)
				return (-1);
			i++;
		}
		else
			structt->arg[j++] = cluster[i];
		i++;
	}
	return (0);
}

void	 ft_cluster_creat(t_state *state)
{
	t_cluster	*head;
	t_cluster	*node;
	int			i;

	i = 0;
	if (state->clean_thrd_argv == NULL)
		return ;
	while (state->clean_thrd_argv[i])
		i++;
	head = (t_cluster *)malloc(sizeof(t_cluster));
	node = head;
	i--;
	while (i)
	{
		node->next = (t_cluster *)malloc(sizeof(t_cluster));
		node = node->next;
		i--;
	}
	node->next = NULL;
	state->cluster = head;
}

void	ft_lenght(t_cluster *structt, char **cluster)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (cluster[i])
	{
		if ((ft_strcmp(cluster[i], ">") != 0 && ft_strcmp(cluster[i], "<") != 0)
			&& (ft_strcmp(cluster[i - 1], ">") != 0
				&& ft_strcmp(cluster[i - 1], "<") != 0))
			len++;
		i++;
	}
	structt->arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (structt->arg == NULL)
		perror("arg");
	i = 0;
	while (i < len)
	{
		structt->arg[i] =NULL;
		i++;
	}
	structt->arg[i] = NULL;
}

void	ft_add_cluster(t_state *state)
{
	///ft_cluster_creat yeniden yazılacak
	t_cluster	*tmp;
	int			i;

	i = 0;
	ft_cluster_creat(state);
	tmp = state->cluster;
	while (state->clean_thrd_argv[i])
	{
		tmp->cmd = state->clean_thrd_argv[i][0];
		ft_lenght(tmp, state->clean_thrd_argv[i]);
		if (ft_args_add(state, state->clean_thrd_argv[i], tmp) == -1)
			return ;
		tmp = tmp->next;
		i++;
	}
	//ft_free_thrd_str(state->clean_thrd_argv); leak yiyor
}


