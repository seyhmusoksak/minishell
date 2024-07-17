/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:34:49 by ekose             #+#    #+#             */
/*   Updated: 2024/07/17 18:34:51 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cmd_get(t_state *state)
{
	char	*tmp;
	char	*command;
	int i=0;

	while (state->sep_path[i])
	{
		tmp = ft_strjoin(state->sep_path[i], "/");
		command = ft_strjoin(tmp, state->lexer->command);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	ft_exec(t_state *state)
{
	char	*cmd_path;

	cmd_path = ft_cmd_get(state);
	if (cmd_path == NULL)
		write(2, "Command not found", ft_strlen("Command not found"));

	if (execve(cmd_path, &state->lexer->command, NULL) == -1)
		write(2, "execv", ft_strlen("execv"));
}

