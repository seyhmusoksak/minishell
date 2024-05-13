/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soksak <soksak@42istanbul.com.tr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 02:11:29 by soksak            #+#    #+#             */
/*   Updated: 2024/05/13 12:26:54 by soksak           ###   ########.fr       */
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
	return (new);
}

static int	find_lexer_type(char *cmd)
{
	if (ft_strncmp(cmd, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(cmd, ">", 1) == 0)
		return (OUTPUT);
	else if (ft_strncmp(cmd, "<", 1) == 0)
		return (INPUT);
	else if (ft_strncmp(cmd, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(cmd, "<<", 2) == 0)
		return (HEREDOC);
	else
		return (ARG);
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

t_lexer	*add_lexer_node(char *line)
{
	t_lexer	*tmp_node;
	char	**splitted_cmds;
	int		i;

	i = 0;
	splitted_cmds = ft_split(line, ' ');
	tmp_node = NULL;
	while (splitted_cmds[i])
	{
		lexer_addback(&tmp_node, new_lexer_node(get_command(splitted_cmds[i]),
				find_lexer_type(splitted_cmds[i])));
		i++;
	}
	//free_split(splitted_cmds);
	return (tmp_node);
}

void lexer_splitter(char **parsed_cmds, t_state *state)
{
	int		i;

	i = 0;
	while (parsed_cmds[i])
	{
		state->lexer[i] = add_lexer_node(parsed_cmds[i]);
		i++;
	}
	state->lexer[i] = NULL;
	//free_split(parsed_cmds);
}
