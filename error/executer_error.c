/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:07:29 by ekose             #+#    #+#             */
/*   Updated: 2024/08/06 18:02:11 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_executer_error(char	**cmd, char *s, int exit_code)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ":", 1);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(exit_code);
}
