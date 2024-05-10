/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:31:02 by ekose             #+#    #+#             */
/*   Updated: 2024/05/10 16:53:22 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	//write fonkiyonu standart çıktı fd ile değiştirilecek
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
	}
	else
		perror("PWD");

}
