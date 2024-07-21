/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   united_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:33:05 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/21 17:30:57 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_united_dolar(t_parser *parser, t_env *env)
{
	char	*dest;
	int		chck_dolr;
	int		chck_dq;

	if (ft_strchr(parser->key, '\'') && ft_strchr(parser->key, '"'))
		ft_clear_for_dolr('\'', parser);
	ft_united_handler(&chck_dq, &chck_dolr, parser, env);
	dest = ft_resizer(parser->united_env);
	ft_free_double_str(parser->united_key);
	// ft_free_double_str(parser->united_env);
	return (dest);
}

int	ft_clear_for_dolr(char quote_type, t_parser *parser)
{
	int		i;
	int		j;
	char	*tmp;
	int		count;

	count = ft_count_quote(parser->key, ft_strlen(parser->key), quote_type);
	tmp = malloc(sizeof(char) * (ft_strlen(parser->key) - count +1));
	if (!tmp)
		return (0);
	i = -1;
	j = 0;
	while (parser->key[++i])
		if (parser->key[i] != quote_type)
			tmp[j++] = parser->key[i];
	tmp[j] = '\0';
	free(parser->key);
	parser->key = ft_strdup(tmp);
	return (1);
}

int	ft_mini_dolar_counter(char *str, int ***chck_dolr, int ***chck_dq)
{
	int		i;
	int		count_dolr;
	int		len;

	len = (ft_strlen(str) -1);
	if (str[len] == '$')
		***chck_dolr = 1;
	else if (str[len] == '"' && len -1 >= 0 && str[len -1] == '$')
		***chck_dq = 1;
	count_dolr = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (***chck_dolr == 1 && i == len)
				break ;
			count_dolr++;
		}
	}
	return (count_dolr + 1);
}

int	ft_init_united(int **chk_dq, int **chk_dolr, char **tmp, t_parser *prs)
{
	int	count;
	int	len;
	int	check_sub;

	check_sub = 0;
	len = ft_strlen(prs->key);
	count = ft_mini_dolar_counter(prs->key, &chk_dolr, &chk_dq);
	if (**chk_dq)
		*tmp = ft_strdup(prs->key + len -2);
	if (prs->key[len -1] == '"' && len - 2 >= 0
		&& (ft_isalnum(prs->key[len -2]) && prs->key[len -2] != '_'))
	{
		check_sub = 1;
		prs->united_key = ft_split(ft_substr(prs->key, 0, len -1), '$');
	}
	else
		prs->united_key = ft_split(prs->key, '$');
	prs->united_env = malloc(sizeof(char *) * (count +1));
	if (!prs->united_env)
		return (0);
	prs->united_env[count] = NULL;
	return (check_sub);
}

void	ft_united_handler(int *chk_dq, int *chk_dlr, t_parser *prs, t_env *env)
{
	int		i;
	int		check_sub;
	char	*tmp;

	*chk_dq = 0;
	*chk_dlr = 0;
	check_sub = 0;
	i = -1;
	check_sub = ft_init_united(&chk_dq, &chk_dlr, &tmp, prs);
	while (prs->united_key[++i])
		prs->united_env[i] = ft_dup_key
			(prs->united_key[i], ft_strlen(prs->united_key[i]), env);
	i--;
	if (*chk_dq)
	{
		prs->united_env[i] = ft_strjoin(prs->united_env[i], tmp);
		free(tmp);
	}
	else if (check_sub)
		prs->united_env[i] = ft_strjoin(prs->united_env[i], "\"");
	else if (*chk_dlr)
		prs->united_env[i] = ft_strjoin(prs->united_env[i], "$");
}