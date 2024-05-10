/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:02:28 by musozer           #+#    #+#             */
/*   Updated: 2024/05/10 19:19:34 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_parser(t_state *state)
{
	t_parser	*parser;
	int			i;
	char		*temp;

	i = 0;
	parser = (t_parser *)malloc(sizeof(t_parser));
	parser->pars = ft_split(state->line, '|');

	while (parser->pars[i])
	{
		temp = ft_strtrim(parser->pars[i], " ");
		free(parser->pars[i]);
		parser->pars[i] = temp;
	}

}
void	cmd_pars(char **pars)
{

	int	i;
	int	j;
	int	k;

	j = 0;
	i = 0;
	while (pars[i])
	{
		while (pars[i][j])
		{
			// tırnak kaldırma işlemi yapılcak libft kütüphanesindeki fonk kullan daha kısa olur
			// sonra oparetör ve flag kontrollerini yap


		}
		j = 0;
		i++;
	}

}

