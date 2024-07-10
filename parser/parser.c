/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:01 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/10 20:39:22 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_state *state)
{
	char	*line;
	char	**tmp_cleaned;
	int		i;
	// int		j;

	line = ft_strtrim(state->line, " ");
	free(state->line);
	//line dadece boşluk ya da enter attığında mac de patlıyır lınux da sıkıntı yok
	if (ft_quote_check(line, (int) ft_strlen(line), state->pars))
		return (ft_exit(line, "Error: open quotation mark", state->pars));
	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
		return (ft_exit(line, "Error: Failure to use pipe ", state->pars));

	tmp_cleaned = ft_init_quote_str
		(ft_pipe_split(line, '|', state->pars), state->pars);

	printf("-------cleaned_argv---------\n");
	i = -1;
	while (tmp_cleaned[++i])
		printf("i(%d): %s\n", i, tmp_cleaned[i]);
	state->pars->clean_argv = ft_get_env(tmp_cleaned, state);

	printf("------------------Put_Env---------------------\n");
	i = -1;
	while (state->pars->clean_argv[++i])
		printf("i(%d): %s\n", i, state->pars->clean_argv[i]);

	// state->clean_thrd_argv = ft_parser_to_lexer(tmp_cleaned, state->pars);

	// printf("-------cleaned_thrd_argv---------\n");
	// i = -1;
	// while (state->clean_thrd_argv[++i])
	// {
	// 	j = -1;
	// 	while (state->clean_thrd_argv[i][++j])
	// 		printf("i(%d) j(%d): %s\n", i, j, state->clean_thrd_argv[i][j]);
	// }
	free(line);
	return (0);
}

char	**ft_init_quote_str(char **str, t_parser *pars)
{
	int		i;
	int		len;

	i = -1;
	len = ft_double_str_len(str);
	pars->src = malloc(sizeof(char *) * (len + 1));
	pars->cleaned = malloc(sizeof(char *) * (len + 1));
	if (!pars->src || !pars->cleaned || !str)
		return (NULL);
	while (str[++i])
	{
		pars->src[i] = ft_strtrim(str[i], " ");
		pars->cleaned[i] = malloc(sizeof(char) * ft_strlen(pars->src[i]) + 1);
	}
	pars->src[i] = NULL;
	pars->cleaned[i] = NULL;
	ft_send_cleaner(pars);
	ft_free_double_str(str);
	ft_free_double_str(pars->src);
	return (pars->cleaned);
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

	i = 0;
	j = -1;

	if ((str[0] == '"' && str[ft_strlen(str) -1] == '"')
		|| (str[0] == '\'' && str[ft_strlen(str) -1] == '\''))
	{
		dest = malloc(sizeof(char) * ft_strlen(str) - 1);
		if (!dest)
			return (NULL);
		while (str[++i] && (i < ((int )ft_strlen(str))))
			dest[++j] = str[i];
		dest[j] = '\0';
		return (dest);
	}
	return (str);
}


