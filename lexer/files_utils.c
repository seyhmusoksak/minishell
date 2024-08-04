/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:39:43 by ekose             #+#    #+#             */
/*   Updated: 2024/08/04 14:41:21 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_files	*ft_files_init(t_files *node)
{

	node = (t_files *) malloc(sizeof(t_files));
	node->error = 0;
	node->output = ft_strdup("");
	node->input = ft_strdup("");
	node->fd_input = 0;
	node->fd_output = 1;
	return (node);
}

static	t_files	*ft_files_init_input(t_files *node, char *arg)
{
	free(node->input);
	node->input = ft_strdup(arg);
	node->fd_input = ft_open_input(node->input);
	if (node->fd_input == -1)
		node->error = 1;
	return (node);
}

static	t_files	*ft_files_init_output(t_files *node, char *arg)
{
	free(node->output);
	node->output = ft_strdup(arg);
	node->fd_output = ft_open_output(node->output);
	if (node->fd_output == -1)
		node->error = 2;
	return (node);
}

t_files	*ft_new_files_node(char **arg)
{
	t_files	*node;
	int		i;

	node = NULL;
	node = ft_files_init(node);
	ft_heredoc_check(node, arg);
	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], "<") == 0)
		{
			node = ft_files_init_input(node, arg[i + 1]);
			if (node->error == 1)
				return (node);
			i++;
		}
		else if (ft_strcmp(arg[i], ">") == 0)
		{
			node = ft_files_init_output(node, arg[i + 1]);
			if (node->error == 2)
				return (node);
			i++;
		}
		i++;
	}
	return (node);
}
