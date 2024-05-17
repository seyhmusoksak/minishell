/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:37:07 by soksak            #+#    #+#             */
/*   Updated: 2024/05/17 12:36:21 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_addback(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp ->next = new;
}

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*get_env(t_state *data, char **env)
{
	int		i;
	int		x;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	(void)data;
	while (env[i])
	{
		x = 0;
		while (env[i][x] && env[i][x] != '=')
			x++;
		env_addback(&tmp, new_env(ft_substr(env[i], 0, x),
				ft_substr(env[i], x + 1, ft_strlen(env[i]) - x - 1)));
		i++;
	}
	return (tmp);
}

char	**ft_sep_path(t_state *state)
{

	while (state->env)
	{
		if (ft_strncmp(state->env->key, "PATH",
				ft_strlen(state->env->key)) == 0)
		{
			state->sep_path = ft_split(state->env->value, ':');
			break ;
		}
		state->env = state->env->next;
	}
	return (state->sep_path);
}
