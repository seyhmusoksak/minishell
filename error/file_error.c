/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:40:08 by ekose             #+#    #+#             */
/*   Updated: 2024/07/30 16:16:36 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_cluster_free(t_cluster *cluster)
{
	int	i;

	i = 0;
	while (cluster->cmd[i])
		free(cluster->cmd[i++]);
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
