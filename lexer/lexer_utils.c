/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soksak <soksak@42istanbul.com.tr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 03:19:30 by soksak            #+#    #+#             */
/*   Updated: 2024/07/19 16:48:03 by soksak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_lexer_pipe(char ***parsed_data)
{
	int	count;

	count = 0;
	while (parsed_data[count])
		count++;
	return (count);
}
t_lexer **my_lexer_nulloc(int count)
{
	int	i;
	t_lexer	**lexer;

	i = 0;
	lexer = (t_lexer **)malloc(sizeof(t_lexer *) * (count + 1));
	while (i < count)
	{
		lexer[i] = NULL;
		i++;
	}
	lexer[i] = NULL;
	return (lexer);
}

void my_lexer_free(t_lexer **lexer)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	while (lexer[i])
	{
		while (lexer[i])
		{
			tmp = lexer[i]->next;
			free(lexer[i]->command);
			free(lexer[i]);
			lexer[i] = tmp;
		}
		i++;
	}
	free(lexer);
}
