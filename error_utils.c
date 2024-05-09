/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:08:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/10 01:13:58 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_0(t_state *state, char *str)
{
	printf("%s\n",str);
	free(state->pars);
	free(state->lexer);
	free(state->env);
	free(state);
	exit (1);
}
