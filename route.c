/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:07:13 by ekose             #+#    #+#             */
/*   Updated: 2024/07/28 21:19:09 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_route(t_state *state)
{
	if (ft_strcmp(state->cluster->cmd, "cd") == 0)
		ft_cd(&state);
	else if (ft_strcmp(state->cluster->cmd,"pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(state->cluster->cmd, "echo") == 0)
		ft_echo(state);

}
