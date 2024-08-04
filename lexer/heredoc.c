/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:23:38 by ekose             #+#    #+#             */
/*   Updated: 2024/08/04 18:53:08 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_heredoc(t_files *node)
{
	int		error;
	int		pid;
	char	*line;

	pipe(node->fd_heredoc);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			line = readline(">");
			if (ft_strcmp(line, node->input) == 0)
			{
				free(line);
				exit(0);
			}
			write(node->fd_heredoc[1], line, ft_strlen(line));
			write(node->fd_heredoc[1], "\n", 1);
			free(line);
		}
	}
	else
		waitpid(pid, &error, 0);
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
}

