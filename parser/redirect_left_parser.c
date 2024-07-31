/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_left_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:09:14 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/30 23:54:31 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_left_redirect(char *str, int len, char type, t_parser *pars)
{
	t_node	*new_node;
	char	*sub;
	char	*join;
	char	*result;
	char	*sub2;

	sub = ft_substr(str, pars->nr, len - pars->nr);
	if (type == 'h')
	{
		sub2 = ft_substr(str, len, 2);
		join = ft_strjoin(sub, " ");
		result = ft_strjoin(join, sub2);
		pars->nr = len + 2;
	}
	else if (type == 'r')
	{
		sub2 = ft_substr(str, len, 1);
		join = ft_strjoin(sub, " ");
		result = ft_strjoin(join, sub2);
		pars->nr = len + 1;
	}
	ft_free_substr(&sub, &sub2, &join);
	pars->control = ++pars->check_redirect;
	new_node = ft_dolar_new(result);
	ft_dolar_add_back(&pars->sublist, new_node);
}

t_node	*ft_finish_redirect(char *str, int i, t_parser *pars)
{
	t_node	*new_node;
	t_node	*dest;
	char	*sub;
	char	*restr;

	if (i != pars->nr)
	{
		sub = ft_substr(str, pars->nr, i - pars->nr);
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

void	ft_check_control(t_parser *parser)
{
	if (parser->control)
	{
		parser->r = parser->nr;
		parser->control = 0;
	}
}

void	ft_free_substr(char **sub, char **sub2, char **sub3)
{
	free (*sub);
	sub = NULL;
	free (*sub2);
	sub2 = NULL;
	free(*sub3);
	sub3 = NULL;
}