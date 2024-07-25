/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:00:18 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/25 21:41:37 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char **ft_redirect_parser(t_parser *pars, t_dolar *list)
{
	int	i;
	t_dolar *new_node;

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

t_dolar	*ft_redirect_handler(char *str ,int i, int j, t_parser *pars)
{
	int	check_redirect;

	pars->sublist = NULL;
	check_redirect = 0;
	while (str[++i])
	{
		if (str[i] == '<' && !ft_quote_check(str, i, pars)
			&& (str[i +1] && str[i +1] == '<')
			&& str[i +2] && str[i +2] != ' ')
			check_redirect += ft_split_redirect(str, (++i +1), &j, pars);
		else if (str[i] == '>' && !ft_quote_check(str, i, pars)
			&& (str[i +1] && str[i +1] == '>')
			&& str[i +2] && str[i +2] != ' ')
			check_redirect += ft_split_redirect(str, (++i +1), &j, pars);
		else if (str[i] == '>' && !ft_quote_check(str, i, pars)
			&& str[i +1] && str[i +1] != ' ')
			check_redirect += ft_split_redirect(str, i+1, &j, pars);
		else if (str[i] == '<' && !ft_quote_check(str, i, pars)
			&& str[i +1] && str[i +1] != ' ')
			check_redirect += ft_split_redirect(str, i+1, &j, pars);
	}
	if (!check_redirect)
		return (ft_dolar_new(str));
	return (ft_finish_redirect(str, i, &j, pars));
}
char	**ft_node_to_double(t_dolar **list, int i, int list_size)
{
	char	**dest;
	t_dolar	*tmp;
	// t_dolar	*tmp2;

	tmp = *list;
	list_size = ft_listlen(*list);
	dest = malloc(sizeof(char *) * (list_size + 1));
	if (!dest)
		return(NULL);
	printf("list_size: %d\n", list_size);
	dest[list_size] = NULL;
	while (tmp)
	{
		dest[i] = ft_strdup(tmp->str);
		printf("node_to_double: %s\n", dest[i]);
		tmp = tmp->next;
		i++;
	}
	// tmp = *list;
	// while (tmp)
	// {
	// 	tmp2 = tmp;
	// 	free(tmp2->str);
	// 	tmp = tmp->next;
	// 	free(tmp2);
	// }
	return (dest);
}

int	ft_split_redirect(char *str, int len, int *j, t_parser *pars)
{
	t_dolar *new_node;
	char	*sub;
	char	*join;

	printf("str_split: %s=len: %d *j: %d\n",str, len, *j);
	sub = ft_substr(str, *j, len - *j);
	printf("sub: %s= %zu\n", sub, ft_strlen(sub));
	join = ft_strjoin(sub, " ");
	printf("join: %s= %zu\n", join, ft_strlen(join));
	new_node = ft_dolar_new(join);
	ft_dolar_add_back(&pars->sublist, new_node);
	*j = len;
	printf("j: %d len: %d\n", *j, len);
	printf("split: %s\n", pars->sublist->str);
	free(sub);
	return (1);
}
t_dolar	*ft_finish_redirect(char *str, int i, int *j, t_parser *pars)
{
	t_dolar *new_node;
	t_dolar	*dest;
	char	*sub;
	char	*restr;

	printf("str_in_finish:%s-i: %d j: %d\n", str, i, *j);
	printf("list:%s\n",pars->sublist->str);
	if (i != *j)
	{
		sub = ft_substr(str, *j, i - *j);
		printf("finish_sub:%s\n", sub);
		new_node = ft_dolar_new(sub);
		ft_dolar_add_back(&pars->sublist , new_node);
		printf("---------------\n");
	}
	restr = ft_node_resizer(pars->sublist);
	printf("finish-rstr:%s\n",restr);
	dest = ft_dolar_new(restr);
	return (dest);
}
int	ft_listlen(t_dolar *lst)
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
