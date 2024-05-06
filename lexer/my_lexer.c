/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 02:11:29 by soksak            #+#    #+#             */
/*   Updated: 2024/05/06 14:38:50 by ekose            ###   ########.fr       */
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
		return (REDIRECT);
	else if (ft_strncmp(cmd, "<", 1) == 0)
		return (REDIRECT);
	else
		return (ARG);
}


static char	*get_only_cmd(char *splitted_cmd)
{
	char	*cmd;
	int		i;

	i = 0;
	if (splitted_cmd[i] == '|' || splitted_cmd[i] == '>'
		|| splitted_cmd[i] == '<')
		return (NULL);
	while (splitted_cmd[i] != '\0')
	{
		if (splitted_cmd[i] == '|' || splitted_cmd[i] == '>'
			|| splitted_cmd[i] == '<')
			return (NULL); //Düzeltilmesi gerek
		i++;
	}
	cmd = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (splitted_cmd[++i] != '\0')
	{
		if (splitted_cmd[i] == '|' || splitted_cmd[i] == '>'
			|| splitted_cmd[i] == '<')
			break ;
		cmd[i] = splitted_cmd[i];
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
		lexer_addback(&tmp_node, new_lexer_node(get_only_cmd(splitted_cmds[i]),
				find_lexer_type(splitted_cmds[i])));
		i++;
	}
	free_split(splitted_cmds);
	return (tmp_node);
}
