/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soksak <soksak@42istanbul.com.tr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:21:19 by soksak            #+#    #+#             */
/*   Updated: 2024/07/19 05:09:26 by soksak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	lexer_addback(t_lexer **lex_node, t_lexer *new)
{
	t_lexer	*tmp;

	if (!lex_node || !new)
		return ;
	if (!*lex_node)
	{
		*lex_node = new;
		return ;
	}
	tmp = *lex_node;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp ->next = new;
}

static t_lexer	*new_lexer_node(char *cmd, int type)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->command = cmd;
	new->type = type;
	new->next = NULL;
	printf("new->command: %s\n", new->command);
	return (new);
}

static int	find_lexer_type(char *cmd)
{
	if (ft_strncmp(cmd, ">", 1) == 0)
		return (INPUT);
	else if (ft_strncmp(cmd, "<", 1) == 0)
		return (OUTPUT);
	else if (ft_strncmp(cmd, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(cmd, "<<", 2) == 0)
		return (HEREDOC);
	else
		return (5);
}

static char	*get_command(char *splitted_cmd)
{
	char	*cmd;
	int		i;

	cmd = (char *)malloc(sizeof(char) * (ft_strlen(splitted_cmd) + 1));
	i = 0;
	while (splitted_cmd[i])
	{
		cmd[i] = splitted_cmd[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

t_lexer	**add_lexer_node(t_state *state)
{
	t_lexer	**tmp_node;
	char ***parsed_data;
	int		i;
	int		j;

	i = 0;
	parsed_data = state->clean_thrd_argv;
	tmp_node = my_lexer_nulloc(count_lexer_pipe(parsed_data));
	while (parsed_data[i])
	{
		j = 0;
		while (parsed_data[i][j])
		{
			lexer_addback(&tmp_node[i], new_lexer_node(get_command(parsed_data[i][j]),
			find_lexer_type(parsed_data[i][j])));
			j++;
		}
		i++;
	}
	return (tmp_node);
}
