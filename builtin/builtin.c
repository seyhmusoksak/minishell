/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:35:15 by ekose             #+#    #+#             */
/*   Updated: 2024/05/09 23:39:13 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env(t_state *state)
{
	t_parser	*tmp;
	t_env		*tmp_env;
	int			i;
	int			j;

	//export komutunun argumansız geldiği durum kontrol edilecek!!
	tmp_env = state->env;
	tmp = state->parser;
	i = 0;
	j = 0;
	while (tmp->arg[i] && ft_strchr(tmp->arg[i], '=') != NULL)
	{
		while (tmp->arg[i][j] && tmp->arg[i][j] != '=' )
			j++;
		env_addback(&tmp_env, new_env(ft_substr(tmp->arg[i], 0, j),
				ft_substr(tmp->arg[i], j + 1, ft_strlen(tmp->arg[i]) - j - 1)));
		i++;
	}
	state->env = tmp_env;
}

// void	ft_del_env(t_state *state)
// {
// }

void	ft_echo(t_state *state)
{
	char	**arg;
	int		i;

	arg = state->parser->arg;
	i = 0;
	while(arg[i] != NULL)
	{
		write (1, arg[i], ft_strlen(arg[i]));
		write (1," ",1);
		i++;
	}
	//-n dışındaki flag kontrolü yapılacak
	if(ft_strncmp(state->parser->flag[0], "-n", 2) != 0)
		write(1, "\n", 1);
}
