/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:58:11 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/21 16:29:43 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_dolar(char *str)
{
	int	i;
	int	count_dolar;

	count_dolar = 0;
	if (ft_strchr(str, '$') != NULL && ft_strlen(str) > 1)
	{
		i = 0;
		while (str[i])
		{
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' && ft_isdolr(str, i))
				count_dolar++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		return (count_dolar);
	}
	return (0);
}

int	ft_isdolr(char *str, int index)
{
	char	*check_str;
	int		start;
	int		dval;
	int		sval;

	if (str[index] == '$' && str[index +1] != '\0' && str[index +1] != ' '
		&& str[index +1] != '"' && str[index +1] != '\''
		&& str[ft_strlen(str)- 1] != '\'')
	{
		start = index;
		while (str[index] != ' ' && str[index])
			index++;
		check_str = ft_substr(str, start, (index - start));
		dval = ft_count_quote(check_str, index - start, '"') % 2;
		sval = ft_count_quote(check_str, index - start, '\'') % 2;
		if ((dval && sval) || (!dval && !sval) || (dval && !sval))
		{
			free(check_str);
			check_str = NULL;
			return (1);
		}
		free(check_str);
		check_str = NULL;
	}
	return (0);
}


t_dolar	*ft_dolar_new(char *content)
{
	t_dolar	*new_node;

	new_node = (t_dolar *)malloc(sizeof(t_dolar));
	if (!new_node)
		return (NULL);
	new_node->str = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_dolar_add_back(t_dolar **lst, t_dolar *new_node)
{
	t_dolar	*temp;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

char	*ft_node_resizer(t_dolar *dolar)
{
	char	*dest;
	t_dolar	*tmp;
	t_dolar	*tmp2;

	tmp = dolar;
	dest = ft_strdup("");
	while (tmp)
	{
		dest = ft_strjoin(dest, tmp->str);
		tmp = tmp->next;
	}
	tmp = dolar;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp2->str);
		tmp = tmp->next;
		free(tmp2);
	}
	return (dest);
}

