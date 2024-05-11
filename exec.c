/* ************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:34:49 by ekose             #+#    #+#             */
/*   Updated: 2024/05/08 16:50:11 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************** */

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
	printf("%s\n\n",cmd_path);
	char *arg[]={"echo","''","Mustafa", "''",NULL};
	pid_t pd = fork();
	if(pd == 0)
	{
		if (execve(cmd_path, arg, NULL) == -1)
			write(2, "execv\n", ft_strlen("execv\n"));
	}
	waitpid(pd,NULL,0);
}
