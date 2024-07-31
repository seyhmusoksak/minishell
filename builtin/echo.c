/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:36:59 by ekose             #+#    #+#             */
/*   Updated: 2024/07/30 18:21:37 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_flag_check(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][j] != '-')
			return (i);
		while (cmd[i][++j])
		{
			if (cmd[i][j] != 'n')
				return (i);
		}
		i++;
	}
	return (i);
}

void	ft_echo(t_cluster *cluster)
{
	char	**cmd;
	int		i;
	int		fd;
	int		index;

	fd = 1;
	index = ft_flag_check(cluster->cmd);
	i = index;
	if (*(cluster->files->output))
		fd = open(cluster->files->output, O_CREAT | O_RDWR, 0777);
	cmd = cluster->cmd;
	if (cmd[1] == NULL)
	{
		write(fd, "\n", 2);
		return ;
	}
	while (cmd[index])
	{
		write(fd, cmd[index], ft_strlen(cmd[index]));
		write(fd, " ", 1);
		index++;
	}
	if (i == 1)
		write(fd, "\n", 1);
}