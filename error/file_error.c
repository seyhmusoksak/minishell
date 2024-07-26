/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:40:08 by ekose             #+#    #+#             */
/*   Updated: 2024/07/26 17:00:40 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_cluster_free(t_state *state)
{
	t_cluster	*tmp;
	t_cluster	*head;
	int			i;

	head = state->cluster;
	while (head)
	{
		printf("aa\n");
		tmp = head->next;
		i = 0;
		while (head->arg[i])
		{
			free(head->arg[i]);
			i++;
		}
		free(head->arg);
		free(head->files->input);
		free(head->files->output);
		free(head);
		head = tmp;
	}
		head = NULL;
}
int	ft_file_open_error(t_state *state, char *file)
{
	(void) state;
	perror(file);
	ft_cluster_free(state);
	return (-1);
}
