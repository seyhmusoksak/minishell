/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:35:15 by ekose             #+#    #+#             */
/*   Updated: 2024/05/15 19:29:45 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_node(t_state **state, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = (*state)->env;
	prev = NULL;
	while (tmp != NULL && ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	if (tmp == (*state)->env)
		(*state)->env = tmp->next;
	if (prev != NULL)
		prev->next = tmp->next;
	free(tmp);
}

void	ft_add_env(t_state **state)
{
	t_parser	*tmp;
	t_env		*tmp_env;
	int			i;
	int			j;

	tmp_env = (*state)->env;
	tmp = (*state)->parser;
	i = 0;
	j = 0;
	while (tmp->arg[i]) // yeni envleri listenin sonuna eklicek
	{
		ft_del_node(state, tmp->arg[i]); //Aynı keyden varsa silmek için
		while (tmp->arg[i][j] && tmp->arg[i][j] != '=' )
			j++;
		env_addback(&tmp_env, new_env(ft_substr(tmp->arg[i], 0, j),
				ft_substr(tmp->arg[i], j + 1, ft_strlen(tmp->arg[i]) - j - 1)));
		i++;
	}
	(*state)->env = tmp_env;
}

void	ft_del_env(t_state **state)//unsettt
{
	t_state	*temp;
	int		i;

	temp = *state;
	i = 0;
	if (temp->parser->arg == NULL)
		return ;
	while (temp->parser->arg[i])
		ft_del_node(state, temp->parser->arg[i++]);
}

void	ft_export_status(t_state **state) // bufonkiyon hatalı düzeltilecek
{
	t_parser	*tmp;
	int			i;

	i = 0;
	tmp = (*state)->parser;
	if (tmp->arg == NULL || tmp->arg[0] == NULL)
		return (ft_print_exp(state));
	while (tmp->arg[i])
	{
		if (ft_strchr(tmp->arg[i], '=') != NULL)
		{
			ft_add_env(state);
			ft_add_exp(state);//yazılacak
		printf("if1=%s\n",tmp->arg[i]);
		}
		else
		{
			ft_add_exp(state);
	printf("if2%s\n",tmp->arg[i]);
		}
		i++;
	}
}
