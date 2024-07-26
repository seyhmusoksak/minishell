/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:08:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/24 16:11:31 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_mesage(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	ft_clean_env(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp2->key);
		free(tmp2->value);
		//free(tmp2->sep_path);
		tmp = tmp->next;
		free(tmp2);
	}

}

int	ft_full_free(t_state *state)
{
	if (!state->parser->exit_check)
		ft_free_double_str(state->parser->clean_argv);
	ft_clean_env(&state->env);
	free(state->parser);
	free(state);
	return (1);
}

void	ft_free_double_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}


int	ft_exit(char *line, char *msg, t_parser *parser)
{
	free(line);
	ft_error_mesage(msg);
	parser->exit_check = 1;
	return (1);
}

void	ft_free_thrd_str(char ***str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			free(str[i][j]);
		free(str[i]);
	}
	free(str);
}
