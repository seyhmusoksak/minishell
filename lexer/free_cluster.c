/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cluster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:31:23 by ekose             #+#    #+#             */
/*   Updated: 2024/08/06 18:20:26 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_all_cluster_free(t_state *state)
{
	t_cluster	*tmp;

	if (!state->cluster)
		return ;
	tmp = state->cluster;
	while (tmp)
	{
		state->cluster = tmp->next;
		ft_free_double_str(tmp->cmd);
		if (tmp->files->input)
			free(tmp->files->input);
		if (tmp->files->output)
			free(tmp->files->output);
		if (tmp->files->heredoc)
			free(tmp->files->heredoc);
		if (tmp->files)
			free(tmp->files);
		free(tmp);
		tmp = state->cluster;
	}
}
