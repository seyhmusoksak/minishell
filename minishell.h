/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/07/01 20:09:22 by mehmyilm         ###   ########.fr       */
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
	int	i;
	int	j;
	int	cspace;
	char	*clean_str;
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
	char		**clean_argv;
	char		***clean_thrd_argv;
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


//		string temizleme
void	ft_clean_str(char *str, char *clean_str,int cspace, int i, int j);
int		ft_is_first(char *str, char keycode, int i);
int	ft_write_in_quote(char *str, char *clean_str, int *j, int *cspace, char keycode, char q);
int		ft_error_mesage(char *str);
void	ft_free_double_str(char **str);
int		ft_double_str_len(char **str);
void	ft_free_double_str(char **str);
int		ft_full_free(t_state *state);

//		dquite kontrolu fonksiyonları
int		ft_quote_len_check(char *str, int len);
int		ft_quote_check(char *str, int len, char *tmp, int i, int j, int check, int sq, int dq);
int		ft_dquote_check(char *str, int *check, int dq);
int		ft_count_quote(char *str, int len, char c);
int		ft_squote_check(char *str, int *check, int sq);
char	*ft_cut_dquote(char *str, int *i, int *j, int len, int *check, int *sq);
char	*ft_cut_squote(char *str, int *i, int *j, int len, int *check, int *dq);

// 3D string
char	***ft_parser_to_lexer(char **str);
char	*ft_clean_first_last_quote(char *str);
#endif
