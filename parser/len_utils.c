/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:50:09 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/15 13:09:07 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_double_str_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_write_double_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("str[%d]: %s\n", i, str[i]);
}

int	ft_exit_redirect(char *line, char *msg, t_state *state)
{
	state->error = 258;
	free(line);
	ft_free_double_str(state->pars->cleaned);
	ft_error_mesage(msg);
	return (0);
}
