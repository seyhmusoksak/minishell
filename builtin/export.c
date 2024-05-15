/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:48:13 by ekose             #+#    #+#             */
/*   Updated: 2024/05/15 19:27:14 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_transaction(t_env **ptr1, int *swapped)
{
	char	*temp;
	char	*tmpvalue;

	temp = (*ptr1)->key;
	tmpvalue = (*ptr1)->value;
	(*ptr1)->key = (*ptr1)->next->key;
	(*ptr1)->value = (*ptr1)->next->value;
	(*ptr1)->next->key = temp;
	(*ptr1)->next->value = tmpvalue;
	*swapped = 0;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	bubble_sort(t_env *exp, int (*cmp)(char *, char *))
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	swapped = 0;
	lptr = NULL;
	if (exp == NULL)
		return ;
	while (!swapped)
	{
		swapped = 1;
		ptr1 = exp;
		while (ptr1->next != lptr)
		{
			if ((*cmp)(ptr1->key, ptr1->next->key) > 0)
			{
				ft_transaction(&ptr1, &swapped);
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	ft_print_exp(t_state **state)
{
	t_env	*tmp;

	tmp = (*state)->env;

	while (tmp)
	{
		printf("declare -x %s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_add_exp(t_state **state)
{
	t_parser	*tmp;
	t_env		*tmp_exp;
	int			i;
	int			j;

	tmp_exp = (*state)->exp;
	tmp = (*state)->parser;
	i = 0;
	j = 0;
	while (tmp->arg[i]) // yeni envleri listenin sonuna eklicek
	{
		ft_del_node(state, tmp->arg[i]); //Aynı keyden varsa silmek için
		while (tmp->arg[i][j] && tmp->arg[i][j] != '=' )
			j++;
		env_addback(&tmp_exp, new_env(ft_substr(tmp->arg[i], 0, j),
				ft_substr(tmp->arg[i], j + 1, ft_strlen(tmp->arg[i]) - j - 1)));
		i++;
	}
	bubble_sort(tmp_exp, ft_strcmp);
	(*state)->exp = tmp_exp;
	ft_print_exp(state);
}
