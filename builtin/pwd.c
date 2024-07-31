/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:31:02 by ekose             #+#    #+#             */
/*   Updated: 2024/07/30 16:57:16 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cluster *cluster)
{
	//write fonkiyonu standart çıktı fd ile değiştirilecek
	char	pwd[1024];
	int		fd;

	fd = 1;
	if (*(cluster->files->output))
		fd = open(cluster->files->output, O_RDWR | O_CREAT, 0777);
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
	}
	else
		perror("PWD");

}
