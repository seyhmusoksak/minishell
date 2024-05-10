/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/05/10 18:06:07 by musozer          ###   ########.fr       */
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

typedef struct s_env
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
	char		**sep_path;
	t_lexer		*lexer;
	t_env		*env;
	char		*line;
}	t_state;

typedef struct s_parser
{
	
	char			**pars;
	char			**arg;
	char			**opr;
	char			**flags;
	t_lexer			**lexer;
	struct t_parser	*next;
}	t_parser;

t_env	*get_env(t_state *state, char **env);
void	env_addback(t_env **lst, t_env *new);
char	**ft_sep_path(t_state *state);
t_lexer	*add_lexer_node(char *line);
void	free_split(char **split);
void	add_parser(t_state *state);

#endif
