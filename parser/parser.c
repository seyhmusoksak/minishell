/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:01 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/07 20:32:50 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_state *state)
{
	char	*line;
	char	**split_str;
	char	**pars_redirect;
	int		i;
	int		j;

	if (ft_wait_for_input(state) == 2)
		return (1);
	if (!ft_wait_for_input(state))
		return (0);
	line = ft_strtrim(state->line, " ");
	if (ft_quote_check(line, (int)ft_strlen(line), state->pars))
		return (ft_exit(line, "Error: Open quotation mark !" , state));
	if (ft_pipe_check(line, state->pars))
		return (ft_exit(line, "Error: Failure to use pipe ! ", state));
	split_str = ft_pipe_split(line, '|', state->pars);
	ft_init_quote_str(split_str, state->pars);
	printf("--------------------cleaned_argv--------------------\n");
	ft_write_double_str(state->pars->cleaned);
	if (ft_redirection_control(state->pars))
		return (ft_exit_redirect(line, "Error: Redirect syntax error !", state));
	free(line);
	pars_redirect = ft_redirect_parser(state->pars, state->dolar);
	// printf("------------------Pars_Redirect---------------------\n");
	// ft_write_double_str(pars_redirect);

	ft_free_double_str(state->pars->cleaned);
	state->pars->clean_argv = ft_put_env(pars_redirect, state);
	// printf("--------------------Put_Env-------------------------\n");
	// ft_write_double_str(state->pars->clean_argv);

	ft_free_double_str(pars_redirect);
	state->cmd_count = ft_double_str_len(state->pars->clean_argv);
	state->clean_thrd_argv = ft_parser_to_lexer(state->pars->clean_argv, state->pars);
	printf("----------------------3d_Str------------------------\n");
	i = -1;
	while (state->clean_thrd_argv[++i])
	{
		j = -1;
		while (state->clean_thrd_argv[i][++j])
			printf("i(%d) j(%d): %s\n", i, j, state->clean_thrd_argv[i][j]);
	}
	ft_free_double_str(state->pars->clean_argv);
	ft_cluster(state);
	ft_free_thrd_str(state->clean_thrd_argv);
	ft_executer(state, 0);
	return (0);
}

int	ft_init_quote_str(char **str, t_parser *pars)
{
	int	i;
	int	len;

	i = -1;
	len = ft_double_str_len(str);
	pars->src = malloc(sizeof(char *) * (len + 1));
	pars->cleaned = malloc(sizeof(char *) * (len + 1));
	if (!pars->src || !pars->cleaned || !str)
		return (0);
	while (str[++i])
	{
		pars->src[i] = ft_strtrim(str[i], " ");
		pars->cleaned[i] = malloc(sizeof(char) * ft_strlen(pars->src[i]) + 1);
		if (!pars->cleaned[i])
			return (0);
	}
	pars->src[i] = NULL;
	pars->cleaned[i] = NULL;
	ft_send_cleaner(pars);
	ft_free_double_str(str);
	ft_free_double_str(pars->src);
	return (1);
}

char	***ft_parser_to_lexer(char **str, t_parser *parser)
{
	int		i;
	int		j;
	char	***dest;

	i = -1;
	dest = malloc(sizeof(char **) * (ft_double_str_len(str) + 1));
	if (!dest)
		return (NULL);
	while (str[++i])
		dest[i] = ft_pipe_split(str[i], ' ', parser);
	dest[i] = NULL;
	i = -1;
	while (dest[++i])
	{
		j = -1;
		while (dest[i][++j])
			dest[i][j] = ft_clean_first_last_quote(dest[i][j]);
	}
	return (dest);
}

char	*ft_clean_first_last_quote(char *str)
{
	int		i;
	int		j;
	char	*dest;
	int		dq;
	int		sq;

	i = 0;
	j = -1;
	dq = (str[0] == '"' && str[ft_strlen(str) - 1] == '"');
	sq = (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'');
	if ((dq || sq) && ft_check_full_char(str + 1))
	{
		dest = malloc(sizeof(char) * ft_strlen(str) - 1);
		if (!dest)
			return (NULL);
		while (str[++i] && (i < ((int)ft_strlen(str))))
			dest[++j] = str[i];
		free (str);
		dest[j] = '\0';
		return (dest);
	}
	return (str);
}

char	**ft_put_env(char **str, t_state *state)
{
	t_env	*env;
	char	**dest;
	int		i;
	int		count_dolr;

	env = state->env;
	dest = malloc(sizeof(char *) * (ft_double_str_len(str) + 1));
	if (!dest)
		return (NULL);
	dest[ft_double_str_len(str)] = NULL;
	i = -1;
	while (str[++i])
	{
		count_dolr = ft_count_dolar(str[i], state->pars);
		env = state->env;
		if (count_dolr)
			dest[i] = ft_dolar_handler(str[i], state->dolar, state->pars, env);
		else
			dest[i] = ft_strdup(str[i]);
	}
	return (dest);
}
