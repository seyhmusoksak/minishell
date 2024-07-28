/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/07/28 14:19:15 by mehmyilm         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	char			**sep_path;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	char				*str;
	struct s_node		*next;

}	t_node;
typedef struct s_parser
{
	// clean func parameter
	int		i;
	int		j;
	int		space;
	char	**cleaned;
	char	**src;
	char	**clean_argv;

	//quote check func parameter
	int		k;
	int		m;
	int		check;
	int		count_sq;
	int		count_dq;
	int		check_if;
	int		exit_check;
	int		char_check;

	//	dolar
	int		len_str[2];
	int		len_dolar[2];
	int		d;
	int		dolar_is_first;
	char	**united_key;
	char	**united_env;
	char	*key;

	//	redirect
	t_node	*sublist;
	int		check_redirect;
}	t_parser;

typedef struct s_lexer
{
	char				*command;
	int					type;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_state
{
	char		***clean_thrd_argv;
	char		**sep_path;
	char		*line;
	t_node		*dolar;
	t_parser	*pars;
	t_lexer		*lexer;
	t_env		*env;
}	t_state;

//			get env functions (4)
t_env	*get_env(t_state *state, char **env);
void	env_addback(t_env **lst, t_env *new);
void	ft_exec(t_state *state);
char	**ft_sep_path(t_state *state);
void	ft_clean_env(t_env **env);

//			parser function (6)
int		ft_parser(t_state *state);
char	**ft_pipe_split(char *line, char c, t_parser *parser);
void	ft_quote_control(char **src, char **tmp, char c, t_parser *parser);
int		pipe_c(char *line, char c, t_parser *parser);
int		ft_wait_for_input(t_state *state);
void	ft_strjoin_and_free(char **dst, char *s2, char c);
int		ft_exit(char *line, char *msg, t_parser *parser);

//			string clean functions (11)
int		ft_init_quote_str(char **str, t_parser *pars);
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

//			quote functions (8)
int		ft_quote_check(char *str, int len, t_parser *pars);
void	ft_init_paremeter(t_parser *pars);
int		ft_quote_handler(char *str, char *tmp, int len, t_parser *pars);
void	ft_quote_handler_helper(char *str, char **tmp, int len, t_parser *prs);
int		ft_quote_count_check(char *str, int *check, char quote_type, int num);
int		ft_count_quote(char *str, int len, char quote_type);
char	*ft_cut_dquote(char *str, int len, t_parser *pars);
char	*ft_cut_squote(char *str, int len, t_parser *pars);

//						Put_env functions (20)
char	**ft_put_env(char **str, t_state *state);
int		ft_count_dolar(char *str ,t_parser *parser);
int		ft_isdolr(char *str, int index, t_parser *pars);
int		ft_check_is_in(char *str, int index, t_parser *parser);
char	*ft_dolar_handler(char *str, t_node *dolar, t_parser *prs, t_env *env);
void	ft_pars_str(char *s, t_parser *prs);
void	ft_pars_str_helper(char *s, t_parser *prs);
t_node	*ft_dolar_new(char *content);
void	ft_dolar_add_back(t_node **lst, t_node *new_node);
char	*ft_node_resizer(t_node *dolar);
char	*ft_env_handler(char *str, t_env *env, t_parser *parser);
char	*ft_find_env(char *str, int n, t_parser *parser, t_env *env);
char	*ft_united_dolar(t_parser *parser, t_env *env);
int		ft_clear_for_dolr(char quote_type, t_parser *parser);
void	ft_united_handler(int *chk_dq, int *chk_dlr, t_parser *prs, t_env *env);
int		ft_init_united(int **chk_dq, int **chk_dolr, char **tmp, t_parser *prs);
int		ft_mini_dolar_counter(char *str, int ***chck_dolr, int ***chck_dq);
int		ft_check_after_key(char *key);
int		ft_check_special(char *str, int i);
char	*ft_dup_key(char *key, int n, t_env *env);
char	*ft_join_key(char *key, int index, t_env *env);
char	*ft_resizer(char **str);

//				Redirect functions(7)
char	**ft_redirect_parser(t_parser *pars, t_node *list);
t_node	*ft_redirect_handler(char *str, int i, int j, t_parser *pars);
int		ft_split_redirect(char *str, int len, int *j, t_parser *pars);
t_node	*ft_finish_redirect(char *str, int i, int *j, t_parser *pars);
char	**ft_node_to_double(t_node **list, int i, int list_size);
int		ft_listlen(t_node *lst);

//				3D string functions (3)
char	***ft_parser_to_lexer(char **str, t_parser *parser);
char	*ft_clean_first_last_quote(char *str);
void	ft_free_thrd_str(char ***str);
#endif
