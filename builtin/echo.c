/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:36:59 by ekose             #+#    #+#             */
/*   Updated: 2024/07/28 21:41:51 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_state *state)
{
	//Write fonksiyonundaki standart çıktı fd ile değişecek

	char	**arg;
	int		i;

	arg = state->cluster->arg;
	i = 0;
	if (arg == NULL)
	{
		if (state->cluster->flag == NULL)
			write(1, "\n", 1);
		return ;
	}
	write (1, arg[i], ft_strlen(arg[i]));
	while (arg[++i] != NULL)
	{
		write (1, " ", 1);
		write (1, arg[i], ft_strlen(arg[i]));
	}
	// -n dışındaki flag kontrolü yapılacak
	if (ft_strncmp(state->cluster->flag[0], "-n", 2) != 0)
		write(1, "\n", 1);
}
