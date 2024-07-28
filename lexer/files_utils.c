/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:39:43 by ekose             #+#    #+#             */
/*   Updated: 2024/07/28 17:58:37 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_files	*ft_files_init(t_files *node)
{

	node = (t_files *) malloc(sizeof(t_files));
	node->error = 0;
	node->output = ft_strdup("");
	node->input = ft_strdup("");
	return (node);
}

static	t_files	*ft_files_init_input(t_files *node, char *arg)
{
	free(node->input);
	node->input = ft_strdup(arg);
	if (ft_open_input(node->input) == -1)
		node->error = 1;
	return (node);
}

static	t_files	*ft_files_init_output(t_files *node, char *arg)
{
	free(node->output);
	node->output = ft_strdup(arg);
	if (ft_open_output(node->output) == -1)
		node->error = 2;
	return (node);
}

t_files	*ft_new_files_node(char **arg)
{
	t_files	*node;
	int		i;

	node = NULL;
	node = ft_files_init(node);
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
