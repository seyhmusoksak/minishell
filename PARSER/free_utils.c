/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:21:02 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/15 13:09:04 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_double_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_free_thrd_str(char ***str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			free(str[i][j]);
		free(str[i]);
	}
	free(str);
}
