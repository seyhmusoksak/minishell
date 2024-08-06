/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:31:02 by ekose             #+#    #+#             */
/*   Updated: 2024/08/02 12:35:14 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cluster *cluster)
{
	//write fonkiyonu standart çıktı fd ile değiştirilecek
	char	pwd[1024];
	int		fd;

	fd = cluster->files->fd_output;
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
	}
	else
		perror("PWD");

}
