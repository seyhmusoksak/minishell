/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:17:17 by ekose             #+#    #+#             */
/*   Updated: 2024/07/28 20:48:55 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

static int	ft_len_loop(char **arg)
{
	int	i;
	int	len;

	i = 3;
	len = 0;
	while (arg[i])
	{
		if ((ft_strcmp(arg[i], ">") != 0 && ft_strcmp(arg[i], "<") != 0)
			&& ft_strncmp("-", arg[i], 1) != 0)
			len++;
		i++;
	}
	return (len);
}

static int	ft_len_arg(char **arg)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (ft_strcmp(arg[0], "<") == 0 || ft_strcmp(arg[0], ">") == 0)
		len = ft_len_loop(arg);
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0)
			i += 2;
		else if (ft_strncmp("-", arg[i], 1) == 0)
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	**ft_find_arg(char **arg)
{
	int		i;
	char	**argumans;
	int		j;

	i = 1;
	j = 0;
	argumans = malloc(sizeof(char *) * (ft_len_arg(arg) + 1));
	if (ft_strcmp(arg[0], "<") == 0 || ft_strcmp(arg[0], ">") == 0)
		i += 2;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0)
			i += 2;
		else if (ft_strncmp("-", arg[i], 1) == 0)
			i++;
		else
			argumans[j++] = ft_strdup(arg[i++]);
	}
	argumans[j] = NULL;
	return (argumans);
}
