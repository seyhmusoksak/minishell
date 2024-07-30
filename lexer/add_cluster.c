/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cluster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:11:58 by ekose             #+#    #+#             */
/*   Updated: 2024/07/30 21:25:02 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL | s2 == NULL)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
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
	new->cmd = ft_fill_cmd(arg);
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


