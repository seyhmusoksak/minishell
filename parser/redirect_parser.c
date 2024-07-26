/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:00:18 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/26 17:26:48 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_redirect_parser(t_parser *pars, t_node *list)
{
	int		i;
	t_node	*new_node;

	list = NULL;
	i = -1;
	while (pars->cleaned[++i])
	{
		if (pipe_c(pars->cleaned[i], '>', pars)
			|| pipe_c(pars->cleaned[i], '<', pars))
			new_node = ft_redirect_handler(pars->cleaned[i], -1, 0, pars);
		else
			new_node = ft_dolar_new(ft_strdup(pars->cleaned[i]));
		ft_dolar_add_back(&list, new_node);
	}
	return (ft_node_to_double(&list, 0, 0));
}

t_node	*ft_redirect_handler(char *str, int i, int j, t_parser *pars)
{
	pars->sublist = NULL;
	pars->check_redirect = 0;
	while (str[++i])
	{
		if (str[i] == '<' && !ft_quote_check(str, i, pars)
			&& (str[i +1] && str[i +1] == '<')
			&& str[i +2] && str[i +2] != ' ')
			ft_split_redirect(str, (++i +1), &j, pars);
		else if (str[i] == '>' && !ft_quote_check(str, i, pars)
			&& (str[i +1] && str[i +1] == '>')
			&& str[i +2] && str[i +2] != ' ')
			ft_split_redirect(str, (++i +1), &j, pars);
		else if (str[i] == '>' && !ft_quote_check(str, i, pars)
			&& str[i +1] && str[i +1] != ' ' && str[i +1] != '>')
			ft_split_redirect(str, i +1, &j, pars);
		else if (str[i] == '<' && !ft_quote_check(str, i, pars)
			&& str[i +1] && str[i +1] != ' ' && str[i +1] != '<')
			ft_split_redirect(str, i +1, &j, pars);
	}
	if (!pars->check_redirect)
		return (ft_dolar_new(ft_strdup(str)));
	return (ft_finish_redirect(str, i, &j, pars));
}

char	**ft_node_to_double(t_node **list, int i, int list_size)
{
	char	**dest;
	t_node	*tmp;
	t_node	*tmp2;

	tmp = *list;
	list_size = ft_listlen(*list);
	dest = malloc(sizeof(char *) * (list_size + 1));
	if (!dest)
		return (NULL);
	dest[list_size] = NULL;
	while (tmp)
	{
		dest[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	tmp = *list;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp2->str);
		tmp = tmp->next;
		free(tmp2);
	}
	return (dest);
}

int	ft_split_redirect(char *str, int len, int *j, t_parser *pars)
{
	t_node	*new_node;
	char	*sub;
	char	*join;

	sub = ft_substr(str, *j, len - *j);
	join = ft_strjoin(sub, " ");
	new_node = ft_dolar_new(join);
	ft_dolar_add_back(&pars->sublist, new_node);
	*j = len;
	pars->check_redirect++;
	free(sub);
	return (1);
}

t_node	*ft_finish_redirect(char *str, int i, int *j, t_parser *pars)
{
	t_node	*new_node;
	t_node	*dest;
	char	*sub;
	char	*restr;

	if (i != *j)
	{
		sub = ft_substr(str, *j, i - *j);
		new_node = ft_dolar_new(sub);
		ft_dolar_add_back(&pars->sublist , new_node);
	}
	restr = ft_node_resizer(pars->sublist);
	dest = ft_dolar_new(restr);
	return (dest);
}

int	ft_listlen(t_node *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
