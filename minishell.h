/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/05/12 18:07:53 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_parser
{
	int					flag_count;
	int					arg_count;
	int					count_comnd;
	int					op_count;
	char				*p_comnd;
	char				**operator;
	char				**flag;
	char				**arg;
	struct s_pars		*next;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			**sep_path;
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
	char		*line;
	t_parser	*pars;
	t_lexer		*lexer;
	t_env		*env;
}	t_state;

t_env	*get_env(t_state *state, char **env);
void	env_addback(t_env **lst, t_env *new);
void	ft_exec(t_state *state);
char	**ft_sep_path(t_state *state);

//				parser function
int		ft_parser(t_state *state);
char	**ft_pipe_split(char *line);
char	**ft_pipe_join(char **str);
char	**ft_clean_quatition(char **str);
void	ft_check_str(char *str, char *clean_str);
int		ft_qutation_check(char *str);
int		ft_qutation_len_check(char *str, int len);
int		ft_error_mesage(char *str);
void	ft_free_double_str(char **str);
int		ft_double_str_len(char **str);
void	ft_free_double_str(char **str);
int		ft_full_free(t_state *state);
#endif
