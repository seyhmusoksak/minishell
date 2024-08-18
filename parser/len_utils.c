/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:50:09 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/18 14:25:26 by musozer          ###   ########.fr       */
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

int	ft_control_red(t_parser *parser, char r, char l)
{
	int	spc;

	spc = 0;
	while (parser->cleaned[parser->one][++parser->two])
	{
		if (parser->cleaned[parser->one][parser->two] == ' '
			|| parser->cleaned[parser->one][parser->two] == '\t')
		{
			spc = 1;
			continue ;
		}
		else if (!spc && parser->cleaned[parser->one][parser->two] == l
		&& (parser->cleaned[parser->one][parser->two + 1] == l
		|| parser->cleaned[parser->one][parser->two + 1] == r))
			return (1);
		else if (spc && (parser->cleaned[parser->one][parser->two + 1] == l
		|| parser->cleaned[parser->one][parser->two + 1] == r))
			return (1);
		else if (!spc && parser->cleaned[parser->one][parser->two] == r)
			return (1);
		else
			return (0);
	}
	return (0);
}
