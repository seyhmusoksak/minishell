/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:40:08 by ekose             #+#    #+#             */
/*   Updated: 2024/07/28 14:53:54 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_cluster_free(t_cluster *cluster)
{
	int	i;

	i = 0;
	free(cluster->cmd);
	while (cluster->arg[i])
		free(cluster->arg[i++]);
	free(cluster->arg);
	i = 0;
	while (cluster->flag[i])
		free(cluster->flag[i++]);
	free(cluster->flag);
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
