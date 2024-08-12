/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:28:13 by ekose             #+#    #+#             */
/*   Updated: 2024/08/12 17:25:25 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static char	*ft_env_find(t_state *state, char *key)
{
	t_env		*tmp;
	t_cluster	*cluster;

	cluster = state->cluster;
	tmp = state->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	ft_tilda_edit(t_state *state, int i, int j, int status)
{
	char	*tmp;
	char	*value;

	value = ft_strdup(ft_env_find(state, "HOME"));
	if (status == 1)
	{
		tmp = ft_strjoin(value, &state->clean_thrd_argv[i][j][1]);
		free(state->clean_thrd_argv[i][j]);
		state->clean_thrd_argv[i][j] = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		free(state->clean_thrd_argv[i][j]);
		state->clean_thrd_argv[i][j] = ft_strdup(value);
	}
	free(value);
}

void	ft_tilda_handler(t_state *state)
{
	int		i;
	int		j;

	i = -1;
	while (state->clean_thrd_argv[++i])
	{
		j = -1;
		while (state->clean_thrd_argv[i][++j])
		{
			if (state->clean_thrd_argv[i][j][0] == '~')
			{
				if (ft_strlen(state->clean_thrd_argv[i][j]) != 1
					&& state->clean_thrd_argv[i][j][1] == '/')
					ft_tilda_edit(state, i, j, 1);
				else if (state->clean_thrd_argv[i][j][1] == '\0')
					ft_tilda_edit(state, i, j, 0);
			}
		}
	}
}
