/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:52:02 by soksak            #+#    #+#             */
/*   Updated: 2024/08/07 20:06:03 by mehmyilm         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>
// # define PERMISSION_DENIED "cd"

# define INPUT 1
# define OUTPUT 2
# define APPEND 3
# define HEREDOC 4


# define IN_CAT 1
# define IN_HERADOC 2
# define IN_PARENT 3
# define BUFFER_SIZE 42
# define MAX 1024

int		sig_status;

typedef struct s_files
{
	int		fd_heredoc[2];
	int		error;
	int		fd_input;
	int		fd_output;
	char	*input;
	char	*output;
	char	*heredoc;
}	t_files;

typedef struct s_cluster
{
	char				**cmd;
	pid_t				pid;
	t_files				*files;
	struct s_cluster	*next;
}	t_cluster;

typedef struct s_env
{
	char			*key;
	char			*value;
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

	//	dolar
	int		len_str[2];
	int		len_dolar[2];
	int		d;
	int		dolar_is_first;
	char	**united_key;
	char	**united_env;
	char	*key;
	int		*ptr_errno;

	//	redirect
	t_node	*sublist;
	int		check_redirect;
	int		control;
	int		nr;
	int		r;

	int		one;
	int		two;
	int		red;
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
	int			cmd_count;
	int			error;
	int			**fd;
	char		**envp;
	t_parser	*pars;
	t_cluster	*cluster;
	t_lexer		**lexer;
	t_env		*env;
	t_env		*exp;
	t_node		*dolar;
}	t_state;


//			get env functions (4)
t_env	*get_env(t_state *state, char **env);
void	env_addback(t_env **lst, t_env *new);
void	free_split(char **split);

void	ft_sep_path(t_state *state);
t_env	*new_env(char *key, char *value);
void	env_addback(t_env **lst, t_env *new);
void	ft_add_env(t_state **state, char *arg);
void	ft_echo(t_cluster *cluster);
void	ft_del_env(t_state **state, t_cluster *cluster);
void	ft_pwd(t_cluster *cluster);
void	ft_cd(t_state **state);
void	ft_notdefine_dir(char *s,t_state *state);
void	ft_cd_error(char *dir, t_state *state);
int		ft_strcmp(char *s1, char *s2);
void	bubble_sort(t_env *exp, int (*cmp)(char *, char *));
void	ft_print_exp(t_state **state, t_cluster *cluster);
void	ft_add_exp(t_state **state, char *arg);
void	ft_del_node(t_env **list, char *key);
void	ft_export_status(t_state **state, t_cluster *cluster);
void	ft_key_error(char *s, char *cmd);
int		ft_key_check(char arg, int index);
void	ft_clean_env(t_env **env);

//			parser function (6)
int		ft_parser(t_state *state);
char	**ft_pipe_split(char *line, char c, t_parser *parser);
void	ft_quote_control(char **src, char **tmp, char c, t_parser *parser);
int		ft_count_real_char(char *line, char c, t_parser *parser);
int		ft_wait_for_input(t_state *state);
void	ft_strjoin_and_free(char **dst, char *s2, char c);
char	**ft_new_split(char *s, char c, t_parser *parser);
int		ft_exit(char *line, char *msg, t_state *state);

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
int		ft_full_free(t_state *state, int status);

//			Char control
int		ft_redirection_control(t_parser *parser);
int		ft_sign_in(t_parser *parser, char c);
int		ft_redirection_in(t_parser *parser, char c, char d);
int		ft_new_redirection(t_parser *parser, char c, char d, int k);
int		ft_redirect(t_parser *parser, int k, char c, char d);
int	ft_exit_redirect(char *line, char *msg, t_state  *state);
int		ft_pipe_check(char *line, t_parser *parser);

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
int		ft_count_dolar(char *str, t_parser *parser);
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
void	ft_united_handler(int *chk_dq, int *chk_dlr, t_parser *prs, t_env *env);
int		ft_init_united(int **chk_dq, int **chk_dolr, char **tmp, t_parser *prs);
char	*ft_put_united_env(char *key, t_parser *pars, t_env *env);
int		ft_mini_dolar_counter(char *str, int ***chck_dolr, int ***chck_dq);
int		ft_check_after_key(char *key);
int		ft_check_special(char c);
char	*ft_dup_key(char *key, t_parser *pars, t_env *env);
char	*ft_join_key(char *key, int index, t_env *env);
char	*ft_resizer(char **str);

//				Redirect functions(11)
char	**ft_redirect_parser(t_parser *pars, t_node *list);
void	ft_heradoc_handler(char *str, t_parser *pars);
t_node	*ft_redirect_handler(char *str, t_parser *pars);
int		ft_right_redirect(char *str, int len, t_parser *pars);
void	ft_left_redirect(char *str, int len, char type, t_parser *pars);
int		ft_listlen(t_node *lst);
char	**ft_node_to_double(t_node **list, int i, int list_size);
t_node	*ft_finish_redirect(char *str, int i, t_parser *pars);
int		ft_check_full_char(char *str);
void	ft_check_control(t_parser *parser);
void	ft_free_substr(char **sub, char **sub2, char **sub3, t_parser *pars);

//				3D string functions (3)
char	***ft_parser_to_lexer(char **str, t_parser *parser);
char	*ft_clean_first_last_quote(char *str);
void	ft_free_thrd_str(char ***str);
void	ft_write_double_str(char **str); //kaldırcam bunu
void	ft_init_signals(void);

void	ft_cluster(t_state *state);
int		ft_strcmp(char *s1, char *s2);
char	**ft_fill_cmd(char **arg);
t_files	*ft_new_files_node(char **arg, int i);
int		ft_open_input(char *file);
int		ft_open_output(char *file);
int		ft_open_append(char *file);
t_cluster	*ft_file_open_error(t_cluster *cluster, char *file);
void	ft_print_env(t_state *state, t_cluster *cluster);
void	ft_route(t_state *state);
int		ft_check_built(t_cluster *cluster);



void	ft_close_pipe(t_state *state, int check);
void	ft_dup_init(t_state *state, t_cluster *cluster, int i,int check);
void	ft_executer_error(char	**cmd, char *s, int exit_code);
void	ft_executer(t_state *state, int i);
void	ft_wait(t_state *state, int check);
void	ft_heredoc_check(t_files *node, char **arg);
char	**ft_find_cmd(char **arg, int len);
char	*get_next_line(int fd);
void	ft_all_cluster_free(t_state *state);
void	ft_built_exit_cmd(t_state *state, t_cluster *cluster);
# endif
