/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:17:17 by ekose             #+#    #+#             */
/*   Updated: 2024/07/30 21:16:29 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_find_cmd(char **arg, int len)
{
	int		i;
	char	**cmd;
	int		j;

	i = -1;
	j = 0;
	cmd = malloc(sizeof(char *) * (len + 1));
	while (arg[++i])
	{
		if (i == 0)
		{
			if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0)
				i++;
			else
				cmd[j++] = ft_strdup(arg[i]);
		}
		else
		{
			if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0)
				i++;
			else if (ft_strcmp(arg[i - 1], ">") != 0 && ft_strcmp(arg[i - 1], "<") != 0)
				cmd[j++] = ft_strdup(arg[i]);
		}
	}
	return (cmd);
}

int	ft_cmd_len(char **arg)
{
	int	i;
	int	len;
	int	rdr;

	i = 0;
	rdr = 0;
	len = 0;
	while (arg[i++])
		len++;
	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0)
			rdr++;
		i++;
	}
	return (len - (rdr * 2));
}

char	**ft_fill_cmd(char **arg)
{
	int		len;
	char	**cmd;

	len = ft_cmd_len(arg);
	cmd = ft_find_cmd(arg, len);
	cmd[len] = NULL;
	return (cmd);
}