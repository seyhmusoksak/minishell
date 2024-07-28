/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cluster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:11:58 by ekose             #+#    #+#             */
/*   Updated: 2024/07/28 21:14:33 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_find_flag(char	**arg)
{
	int		i;
	int		j;
	int		len;
	char	**flag;

	i = 0;
	len = 0;
	j = 0;
	while (arg[i])
	{
		if (ft_strncmp("-", arg[i], 1) == 0)
			len++;
		i++;
	}
	flag = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (arg[i])
	{
		if (ft_strncmp("-", arg[i], 1) == 0)
			flag[j++] = ft_strdup(arg[i]);
		i++;
	}
	flag[j] = NULL;
	return (flag);
}

static char	*ft_find_cmd(char	**arg)
{
	if (ft_strcmp(arg[0], ">") == 0 || ft_strcmp(arg[0], "<") == 0)
	{
		return (ft_strdup(arg[2]));
	}
	else
		return (ft_strdup(arg[0]));
}

static void	ft_cluster_addback(t_cluster **cluster_node, t_cluster *new)
{
	t_cluster	*tmp;

	if (!cluster_node || !new)
		return ;
	if (!*cluster_node)
	{
		*cluster_node = new;
		return ;
	}
	tmp = *cluster_node;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp ->next = new;
}

static t_cluster	*ft_new_cluster_node(char	**arg)
{
	t_cluster	*new;

	new = (t_cluster *)malloc(sizeof(t_cluster));
	new->cmd = ft_find_cmd(arg);
	if (ft_strcmp("cd", new->cmd) == 0 && arg[1] != NULL)
	{
		if (ft_strncmp(arg[1], "-", 1) == 0)
			new->arg = ft_find_flag(arg);
		else
			new->arg = ft_find_arg(arg);
	}
	else
		new->arg = ft_find_arg(arg);
	new->flag = ft_find_flag(arg);
	new->files = ft_new_files_node(arg);
	new->next = NULL;
	if (new->files->error == 2)
		return (ft_file_open_error(new, new->files->output));
	if (new->files->error == 1)
		return (ft_file_open_error(new, new->files->input));
	return (new);
}

void	ft_cluster(t_state *state)
{
	char		***thrd_arg;
	t_cluster	*tmp_node;
	int			i;

	i = 0;
	tmp_node = NULL;
	thrd_arg = state->clean_thrd_argv;
	while (thrd_arg[i])
	{
		ft_cluster_addback(&tmp_node, ft_new_cluster_node(thrd_arg[i]));
		i++;
	}
	state->cluster = tmp_node;
}


