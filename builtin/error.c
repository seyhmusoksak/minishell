/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:57:55 by ekose             #+#    #+#             */
/*   Updated: 2024/05/11 18:41:18 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_notdefine_dir(char *s)
{
	// GELIŞTIRILEBİLİR bunun yerine yeni bir error fonkiyonu
	//standart çıktı fd ile dğiştirilecek

	write(1, "cd: ", 4);
	write(1, s, ft_strlen(s));
	write(1, " ", 1);
	write(1, "not set\n", ft_strlen("not set\n"));
}

void	ft_cd_error(char *dir)
{
	//standart çıktı fd ile dğiştirilecek

	write(1, "cd: ", 4);
	perror(dir);
}
