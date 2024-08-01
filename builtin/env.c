/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:35:15 by ekose             #+#    #+#             */
/*   Updated: 2024/08/01 14:59:45 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_state *state, t_cluster *cluster)
{
	t_env	*tmp;
	int		fd;
	int		i;

	i = 0;
	fd = cluster->files->fd_output;
	tmp = state->env;
	while (tmp)
	{
		write(fd, tmp->key, ft_strlen(tmp->key));
		write(fd, "=", 1);
		write(fd, tmp->value, ft_strlen(tmp->value));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
}

int	ft_key_check(char arg, int index)//key isalnum(a-z A-Z 0-9 '-') kontrolü
{
	if (index == 0 && ft_isdigit(arg) == 1) //0. indeks digit olamaz
		return (0);
	if (ft_isalnum(arg) != 1 && arg != '_')
		return (0);
	return (1);
}

void	ft_del_node(t_env **list, char *key) //env veya exporttan düğüm silmek için
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp != NULL && ft_strncmp(tmp->key, key, ft_strlen(tmp->key))) //gödenrilen keyi envde aramak için
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)//envde keyi buldu mu
		return ;
	if (tmp == *list)//key ilk env ise
		*list = tmp->next;
	if (prev != NULL)
		prev->next = tmp->next;
	free(tmp);
}

void	ft_add_env(t_state **state, char *arg)//yeni env eklemk için
{
	t_env		*tmp_env;
	int			i;

	i = 0;
	tmp_env = (*state)->env;
	ft_del_node(&tmp_env, arg); //Aynı keyden varsa silmek için
	while (arg[i] && arg[i] != '=' )
	{
		if (ft_key_check(arg[i], i) == 0) //key değişkeni kurallara uygun mu (isalnum)
			return ;
		i++;
	}
	env_addback(&tmp_env, new_env(ft_substr(arg, 0, i),
			ft_substr(arg, i + 1, ft_strlen(arg) - i - 1)));
	(*state)->env = tmp_env;
}

void	ft_export_status(t_state **state, t_cluster *cluster) //export komutu
{
	int			i;

	i = 1;
	if (cluster->cmd[i] == NULL)
		return (ft_print_exp(state,cluster));
	while (cluster->cmd[i])
	{
		if (ft_strchr(cluster->cmd[i], '=') != NULL) //export argumanını envye eklenip eklenmiyeceği kontrolü
			ft_add_env(state, cluster->cmd[i]);
		ft_add_exp(state, cluster->cmd[i]);
		i++;
	}
}
