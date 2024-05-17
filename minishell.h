/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/05/17 14:48:41 by ekose            ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

// # define PERMISSION_DENIED "cd"

typedef struct s_parser
{
	char	*cmd;
	char	**arg;
	char	**flag;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_exp;

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
	t_parser	*parser;
	t_env		*exp;
	char		*line;
}	t_state;

t_env	*get_env(t_state *state, char **env);
void	env_addback(t_env **lst, t_env *new);
t_lexer	*add_lexer_node(char *line);
void	free_split(char **split);
void	ft_exec(t_state *state);
char	**ft_sep_path(t_state *state);
t_env	*new_env(char *key, char *value);
void	env_addback(t_env **lst, t_env *new);
void	ft_add_env(t_state **state, char *arg);
void	ft_echo(t_state *state);
void	ft_del_env(t_state **state);
void	ft_pwd(void);
void	ft_cd(t_state **state);
void	ft_notdefine_dir(char *s);
void	ft_cd_error(char *dir);
int		ft_strcmp(char *s1, char *s2);
void	bubble_sort(t_env *exp, int (*cmp)(char *, char *));
void	ft_print_exp(t_state **state);
void	ft_add_exp(t_state **state, char *arg);
void	ft_del_node(t_env **list, char *key);
void	ft_export_status(t_state **state);
void	ft_key_error(char *s, char *cmd);
int		ft_key_check(char arg, int index);
#endif
