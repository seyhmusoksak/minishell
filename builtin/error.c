/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:57:55 by ekose             #+#    #+#             */
/*   Updated: 2024/08/02 13:03:47 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_notdefine_dir(char *s)
{
	// GELIŞTIRILEBİLİR bunun yerine yeni bir error fonkiyonu
	write(2, "cd: ", 4);
	write(2, s, ft_strlen(s));
	write(2, " ", 1);
	write(2, "not set\n", ft_strlen("not set\n"));
}

void	ft_cd_error(char *dir)
{
	//standart çıktı fd ile dğiştirilecek

	write(2, "cd: ", ft_strlen("cd: "));
	perror(dir);
}

void	ft_key_error(char *s, char *cmd)
{
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		write (2, "export: ", ft_strlen("export: "));
	else
		write (2, "unset: ", ft_strlen("unset: "));
	write (2, s, ft_strlen(s));
	write (2, ": not a valid identifier\n",
		ft_strlen(": not a valid identifier\n"));
}
