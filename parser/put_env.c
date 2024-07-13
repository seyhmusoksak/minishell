/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:23:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/14 01:28:16 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_env(char **str, t_state *state)
{
	t_env		*env;
	char		**dest;
	int			i;

	env = state->env;
	dest = malloc(sizeof(char *) * (ft_double_str_len(str) +1));
	if (!dest)
		return (NULL);
	dest[ft_double_str_len(str)] = NULL;
	i = -1;
	while (str[++i])
	{
		env = state->env;
		if (ft_count_check_dolar(str[i], state->pars))
		{
			dest[i] = ft_dolar_handler(str[i],	ft_count_check_dolar(str[i], state->pars), state->pars, env);
		}
		else
			dest[i] = ft_strdup(str[i]);
	}
	return(dest);
}
char	*ft_dolar_handler(char *str,int count_dolar, t_parser *parser, t_env *env)
{
	char	**put_env;
	int		j;

	printf("ft_dolar_handler\n");
	parser->d = 0;
	j = 0;
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>> count doalr : %d\n",count_dolar);
	put_env = malloc(sizeof(char *) * (count_dolar +1));
	if (!put_env)
		return (NULL);
	put_env[count_dolar] = NULL;
	while (str[parser->d])
	{
		if (str[parser->d] == '$' && ft_dolar_check(str , parser->d, parser))
			parser->first = 1; // doların başta olduğu koşul
		else
			parser->first = 0;
		ft_pars_str(str, parser);
		put_env[j++] = ft_join_env(str, env, parser);
	}
	int	c= -1;
	while (put_env[++c])
		printf("check: %s\n",put_env[c]);
	printf("handler bitt\n");
	return (ft_resizer(put_env));
}
void	ft_pars_str(char *str, t_parser *parser)
{
	if (parser->first)
	{
		printf("--------------------1---------------------\n");
		// printf("if_first[%d] = %c\n", parser->d, str[parser->d]);
		parser->len_dolar[0] = parser->d +1;
		// printf("if_len_dolar[0] = %d -> %c\n",parser->len_dolar[0], str[parser->len_dolar[0]]);
		while(str[parser->d] != '\0' && str[parser->d] != ' ')
			parser->d++;
		parser->len_dolar[1] = parser->d -1;
		if (ft_check_null(str, &parser->len_str[0], parser->d))
			return ;
		// printf("else_len_dolar[1] = %d -> %c\n",parser->len_dolar[1], str[parser->len_dolar[1]]);
		parser->len_str[0] = parser->d;
		// printf("if_len_str[0] = %d -> %c\n",parser->len_str[0], str[parser->len_str[0]]);
		while((str[parser->d] && str[parser->d] != '$') || (str[parser->d] && str[parser->d] == '$'
			&& !ft_dolar_check(str, parser->d, parser)))
			parser->d++;
		parser->len_str[1] = parser->d -1;
		// printf("if_len_str[1] = %d -> %c\n",parser->len_str[1], str[parser->len_str[1]]);
	}
	else
	{
		printf("-------------------2--------------------\n");
		parser->len_str[0] = parser->d;
		while((str[parser->d] && str[parser->d] != '$') || (str[parser->d] && str[parser->d] == '$'
			&& !ft_dolar_check(str, parser->d, parser)))
			parser->d++;
		parser->len_str[1] = parser->d -1;
		if (ft_check_null(str, &parser->len_dolar[0],parser->d))
			return ;
		parser->len_dolar[0] = parser->d +1;
		while(str[parser->d] != '\0' && str[parser->d] != ' ')
			parser->d++;
		parser->len_dolar[1] = parser->d -1;
	}
}


char	*ft_join_env(char *str, t_env *env, t_parser *parser)
{
	char	*tmp_str;
	char	*env_str;
	char	*dest;

	if (parser->len_str[0] == -1)
		tmp_str = ft_strdup("");
	else
		tmp_str = ft_substr(str, parser->len_str[0], parser->len_str[1] - parser->len_str[0] +1);
	if (parser->len_dolar[0] == -1)
		env_str = ft_strdup("");
	else
		env_str = ft_find_env(str + parser->len_dolar[0] , parser->len_dolar[1] - parser->len_dolar[0] +1, env);

	printf("join_tmp_str  : %s\n", tmp_str);
	printf("join_env_str  : %s\n", env_str);
	if (parser->first)
		dest = ft_strjoin(env_str, tmp_str);
	else
		dest = ft_strjoin(tmp_str, env_str);
	printf("join_dest  : %s\n", dest);
	free(tmp_str);
	tmp_str = NULL;
	free(env_str);
	env_str = NULL;
	return (dest);
}

int	ft_count_check_dolar(char *str, t_parser *parser)
{
	int	i;
	int	count_dolar;

	count_dolar = 0;
	if (ft_strchr(str, '$') != NULL && ft_strlen(str) > 1)
	{
		i = 0;
		while (str[i])
		{
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' && (str[i +1] && str[i +1] != ' ')
				&& ft_quote_check(str + i, ft_strlen(str), parser) != 1)
				count_dolar++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		if (ft_check_loc_dolar(str, parser))
			return(count_dolar);
		else
			return(count_dolar +1);
	}
	return (0);
}
int	ft_dolar_check(char *str, int index, t_parser *parser)
{
	char	*check_str;
	int		start;

	if (ft_quote_check(str, index + 2, parser) != 1)
	{
		start = index;
		while (str[index] != ' ' && str[index])
			index++;
		check_str = ft_substr(str, start, index);
		if (ft_strlen(check_str) > 1)
		{
			free(check_str);
			check_str = NULL;
			return (1);
		}
		free(check_str);
		check_str = NULL;
	}
	return (0);
}
char	*ft_find_env(char *str, int n, t_env *env)
{
	char	*key;
	char	*dest;

	key = ft_substr(str, 0, n);
	if (!key || !str)
		return (NULL);
	if (!ft_check_after_key(key))
		dest = ft_dup_key(key, n, env);
	else
		dest = ft_join_key(key, ft_check_after_key(key), env);
	free(key);
	return (dest);
}
char	*ft_join_key(char *key, int index, t_env *env)
{
	char	*new_key;
	char	*after_key;
	char	*dest;

	new_key = ft_substr(key, 0, index);
	after_key = ft_substr(key, index, ft_strlen(key));
	while (env != NULL)
	{
		if (ft_strncmp(new_key, env->key, index) == 0)
		{
			dest = ft_strjoin(env->value, after_key);
			free(new_key);
			free(after_key);
			return (dest);
		}
		env = env->next;
	}
	free(new_key);
	return (after_key);
}

char	*ft_dup_key(char *key, int n, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, n) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
int	ft_check_after_key(char *key)
{
	int		i;
	int		check_isalnum;

	check_isalnum = 0;
	i = 0;
	while(key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '<' && key[i] != '>')
		{
			check_isalnum = 1;
			break ;
		}
		i++;
	}
	if (check_isalnum)
		return (i);
	return(0);
}
char	*ft_resizer(char **str)
{
	char	*line;
	int		i;

	printf("resizer : %s\n",str[0]);
	line = ft_strdup("");
	i = -1;
	while (str[++i])
		line = ft_strjoin(line, str[i]);
	printf("line: %s\n",line);
	ft_free_double_str(str);
	return (line);
}

int	ft_check_null(char *str, int *value, int index)
{
	if (index >= (int)ft_strlen(str) -1)
	{
		*value = -1;
		return (1);
	}
	return (0);
}

int	ft_check_loc_dolar(char *str, t_parser *parser)
{
	int	len;
	int	i;
	char *tmp;

	len = ft_strlen(str) -1;
	i = len;
	while (i >= 0 && str[i] != ' ')
		i--;
	tmp = ft_substr(str, i +1, len - i);
	if (ft_dolar_check(tmp, 0, parser) && ft_strchr(tmp, '$'))
	{
		free(tmp);
		tmp = NULL;
		return (1);
	}
	free(tmp);
	tmp = NULL;
	return (0);
}
