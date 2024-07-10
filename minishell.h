/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/07/10 16:27:33 by mehmyilm         ###   ########.fr       */
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
	// clean func parameter
	int		i;
	int		j;
	int		space;
	char	**cleaned;
	char	**src;

	//quote check func parameter
	int		k;
	int		m;
	int		check;
	int		count_sq;
	int		count_dq;
	int		check_if;

	int		exit_check;
	int		char_check;
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

//			parser function
int		ft_parser(t_state *state);
char	**ft_pipe_split(char *line, char c, t_parser *parser);
void	ft_quote_control(char **src, char **tmp, char c, t_parser *parser);
int		pipe_c(char *line, char c, t_parser *parser);
void	ft_strjoin_and_free(char **dst, char *s2, char c);
int		ft_exit(char *line, char *msg, t_parser *parser);

//		string temizleme
char	**ft_init_quote_str(char **str, t_parser *pars);
void	ft_send_cleaner(t_parser *parser);
void	ft_cleaner(t_parser *pars, int i);
void	ft_cleaner_helper(t_parser *prs, int *i);
int		ft_is_first(char *str, char keycode, int i, t_parser *pars);
int		ft_write_in_quote(char *str, char cod, char q, t_parser *prs);
int		ft_error_mesage(char *str);
void	ft_free_double_str(char **str);
int		ft_double_str_len(char **str);
void	ft_free_double_str(char **str);
int		ft_full_free(t_state *state);

//		dquite kontrolu fonksiyonları
int		ft_quote_check(char *str, int len, t_parser *pars);
void	ft_init_paremeter(t_parser *pars);
int		ft_quote_handler(char *str, char *tmp, int len, t_parser *pars);
void	ft_quote_handler_helper(char *str, char **tmp, int len, t_parser *prs);
int		ft_quote_count_check(char *str, int *check, char quote_type, int num);
int		ft_count_quote(char *str, int len, char quote_type);
char	*ft_cut_dquote(char *str, int len, t_parser *pars);
char	*ft_cut_squote(char *str, int len, t_parser *pars);

//		3D string
char	***ft_parser_to_lexer(char **str, t_parser *parser);
char	*ft_clean_first_last_quote(char *str);
#endif
