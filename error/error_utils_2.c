/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:40:08 by ekose             #+#    #+#             */
/*   Updated: 2024/08/15 13:08:03 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cluster_free(t_cluster *cluster)
{
	int	i;

	i = 0;
	while (cluster->cmd[i])
		free(cluster->cmd[i++]);
	if (cluster->files->heredoc)
		free(cluster->files->heredoc);
	free(cluster->cmd);
	free(cluster->files->input);
	free(cluster->files->output);
	free(cluster->files);
	free(cluster);
}

t_cluster	*ft_file_open_error(t_cluster *cluster, char *file)
{
	perror(file);
	ft_cluster_free(cluster);
	return (NULL);
}

void	ft_executer_error(char	**cmd, char *s, int exit_code)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ":", 1);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(exit_code);
}
