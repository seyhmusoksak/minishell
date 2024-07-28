/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:00:18 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/28 21:47:31 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_redirect_parser(t_parser *pars, t_node *list)
{
	int		i;
	t_node	*new_node;

	list = NULL;
	i = -1;
	pars->r = 0;
	while (pars->cleaned[++i])
	{
		if (pipe_c(pars->cleaned[i], '>', pars)
			|| pipe_c(pars->cleaned[i], '<', pars))
			new_node = ft_redirect_handler(pars->cleaned[i], -1, pars);
		else
			new_node = ft_dolar_new(ft_strdup(pars->cleaned[i]));
		ft_dolar_add_back(&list, new_node);
	}
	return (ft_node_to_double(&list, 0, 0));
}

t_node	*ft_redirect_handler(char *str, int i, t_parser *pars)
{
	pars->sublist = NULL;
	pars->check_redirect = 0;
	while (str[++i])
	{
		pars->check_heradoc = 0;
		ft_heradoc_handler(str, &i, pars);
		if (str[i] == '>' && !ft_quote_check(str, i, pars)
			&& str[i +1] && str[i +1] != ' ' && str[i +1] != '>'
			&& !pars->check_redirect)
			ft_split_redirect(str, i +1, pars);
		else if (str[i] == '<' && !ft_quote_check(str, i, pars)
			&& str[i +1] && str[i +1] != ' ' && str[i +1] != '<'
			&& !pars->check_redirect)
			ft_split_redirect(str, i +1, pars);
	}
	if (!pars->check_redirect)
		return (ft_dolar_new(ft_strdup(str)));
	return (ft_finish_redirect(str, i, pars));
}
void	ft_heradoc_handler(char *str, int *i, t_parser *pars)
{
	if (str[*i] == '<' && !ft_quote_check(str, *i, pars)
		&& (str[*i +1] && str[*i +1] == '<')
		&& str[*i +2] && str[*i +2] != ' ')
		pars->check_redirect = ft_split_redirect(str, (++(*i) +1), pars);
	if (str[*i] == '<' && !ft_quote_check(str, *i, pars)
		&& (str[*i +1] && str[*i +1] == '<')
		&& str[*i -1] && str[*i -1] != ' ')
		pars->check_redirect = ft_split_redirect(str, (--(*i) +1), pars);
	else if (str[*i] == '>' && !ft_quote_check(str, *i, pars)
		&& (str[*i +1] && str[*i +1] == '>')
		&& str[*i +2] && str[*i +2] != ' ')
		pars->check_redirect = ft_split_redirect(str, (++(*i) +1), pars);
	if (str[*i] == '>' && !ft_quote_check(str, *i, pars)
		&& (str[*i +1] && str[*i +1] == '>')
		&& str[*i -1] && str[*i -1] != ' ')
		pars->check_redirect = ft_split_redirect(str, (--(*i) +1), pars);
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

int	ft_split_redirect(char *str, int len, t_parser *pars)
{
	t_node	*new_node;
	char	*sub;
	char	*join;

	sub = ft_substr(str, pars->r, len - pars->r);
	join = ft_strjoin(sub, " ");
	new_node = ft_dolar_new(join);
	ft_dolar_add_back(&pars->sublist, new_node);
	pars->r = len;
	pars->check_redirect++;
	free(sub);
	return (1);
}

t_node	*ft_finish_redirect(char *str, int i, t_parser *pars)
{
	t_node	*new_node;
	t_node	*dest;
	char	*sub;
	char	*restr;

	if (i != pars->r)
	{
		sub = ft_substr(str, pars->r, i - pars->r);
		new_node = ft_dolar_new(sub);
		ft_dolar_add_back(&pars->sublist, new_node);
	}
	restr = ft_node_resizer(pars->sublist);
	dest = ft_dolar_new(restr);
	return (dest);
}

int	ft_check_full_char(char *str)
{
	int	i;

	i = 0;
	while (i < (int)(ft_strlen(str) -1) && str[i])
	{
		if (str[i] == '>' || str[i] == ' ' || str[i] == '<')
			i++;
		else
			return (1);
	}
	return (0);
}
