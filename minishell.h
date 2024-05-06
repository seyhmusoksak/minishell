/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/05/06 13:53:31 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ARG 0
# define PIPE 1
# define REDIRECT 2

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef	struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_lexer
{
	char				*command;
	int					type;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_state
{
	t_lexer	*lexer;
	t_env	*env;
	char	*line;
}	t_state;

t_env	*get_env(t_state *state, char **env);
void	env_addback(t_env **lst, t_env *new);
t_lexer	*add_lexer_node(char *line);
void	free_split(char **split);

#endif
