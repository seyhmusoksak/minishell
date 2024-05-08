/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:35:15 by ekose             #+#    #+#             */
/*   Updated: 2024/05/08 17:19:06 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_add_env(t_state *state)
{
	t_parser	*tmp;
	t_env		*tmp_env;
	int			i;
	int			j;

	tmp_env = state->env;
	tmp = state->parser;
	i = 0;
	j = 0;
	while (arg[i] && ft_strchr(arg[i], '=') != NULL)
	{
		while (arg[i][j] && arg[i][j] != '=' )
			j++;
		env_addback(&tmp, new_env(ft_substr(arg[i], 0, j),
				ft_substr(arg[i], j + 1, ft_strlen(arg[i]) - j - 1)));
		i++;
	}
	state->env = tmp;
}

void	ft_del_env(t_state *state)
{
	t_env	*tmp_env;
	t_parser	*tmp_pars;

	tmp_env = state->env;
	tmp_pars = state->parser;
	
}
