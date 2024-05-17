/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:16:26 by ekose             #+#    #+#             */
/*   Updated: 2024/05/17 17:38:56 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_value_check(t_state **state, char *key, char *value)
{
	t_env	*tmp;
	int		check;

	check = 1;
	tmp = (*state)->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0
			&& ft_strcmp(tmp->value, value) == 0)
			check = 0;
		tmp = tmp->next;
	}
	return (check);
}

static int	ft_del_if(t_state **state, int i, int j)//key ve value envde ki key ve value ile eşleşiyor mu
{
	t_parser	*tmp;
	char		*value;
	char		*key;

	tmp = (*state)->parser;
	if (ft_strchr(tmp->arg[i], '=') != NULL)
	{
		key = ft_substr(tmp->arg[i], 0, j);
		value = ft_substr(tmp->arg[i], j + 1,
				ft_strlen(tmp->arg[i]) - j - 1);
		if (ft_value_check(state, key, value) == 1)
		{
			ft_key_error(tmp->arg[i], "unset");
			free(key);
			free(value);
			return (1);
		}
		free(key);
		free(value);
	}
	return (0);
}

void	ft_del_env(t_state **state)
{
	t_parser	*tmp;
	int			i;
	int			j;

	i = 0;
	tmp = (*state)->parser;
	while (tmp->arg[i])
	{
		j = 0;
		while (tmp->arg[i][j] && tmp->arg[i][j] != '=')
		{
			if (ft_key_check(tmp->arg[i][j], j) == 0)
				ft_key_error(tmp->arg[i], "unset");
			j++;
		}
		if (ft_del_if(state, i, j) == 0)
		{
			ft_del_node(&(*state)->env, tmp->arg[i]);
			ft_del_node(&(*state)->exp, tmp->arg[i]);
		}
		i++;
	}
}
