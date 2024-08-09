/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:23:38 by ekose             #+#    #+#             */
/*   Updated: 2024/08/09 18:57:00 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	ft_heradoc_helper(char *line, t_files *node)
{
	if (line == NULL)
	{
		close(node->fd_heredoc[1]);
		exit(0);
	}
	if (ft_strcmp(line, node->input) == 0)
	{
		free(line);
		exit(0);
	}
	write(node->fd_heredoc[1], line, ft_strlen(line));
	write(node->fd_heredoc[1], "\n", 1);
	free(line);
}

static void	ft_heredoc(t_files *node)
{
	int		error;
	int		pid;
	char	*line;

	pipe(node->fd_heredoc);
	pid = fork();
	if (pid == 0)
	{
		sig_status = IN_HERADOC;
		while (1)
		{
			line = readline(">");
			ft_heradoc_helper(line, node);
		}
	}
	else
	{
		sig_status = IN_PARENT;
		waitpid(pid, &error, 0);
	}
	close(node->fd_heredoc[1]);
}

void	ft_heredoc_check(t_files *node, char **arg)
{
	int		i;

	i = 0;
	node->heredoc = ft_strdup("");
	while (arg[i])
	{
		if (ft_strcmp(arg[i], "<<") == 0)
		{
			free(node->heredoc);
			free(node->input);
			node->input = ft_strdup(arg[i + 1]);
			ft_heredoc(node);
			node->heredoc = get_next_line(node->fd_heredoc[0]);
			close(node->fd_heredoc[0]);
			i++;
		}
		i++;
	}
	if (node->heredoc == NULL)
		node->heredoc = ft_strdup("");
}
