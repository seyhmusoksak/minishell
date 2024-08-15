/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:10:49 by ekose             #+#    #+#             */
/*   Updated: 2024/08/15 13:08:51 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_open_output(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	ft_open_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	ft_open_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}
