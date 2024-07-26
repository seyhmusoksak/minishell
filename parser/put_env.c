/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:23:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/18 13:54:17 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TEST MWTNİ:
// "e"c"h"o '$USER' "a'm'a bu kez $USER.dayii $" | ls -a "$PWD $USER" $PWD "$USER" | c"a"t "a"."txt b'.'txt" "$DAYI" | "Deneyin $USER sizde"

char	*ft_dolar_handler(char *str, int cnt_dolr, t_parser *pars, t_env *env)
{
	char	**put_env;
	int		j;

	pars->d = 0;
	j = 0;
	put_env = malloc(sizeof(char *) * (cnt_dolr +1));
	if (!put_env)
		return (NULL);
	put_env[cnt_dolr] = NULL;
	while (str[pars->d])
	{
		if (str[pars->d] == '$' && ft_isdolr(str, pars->d, pars))
			pars->dolar_is_first = 1;
		else
			pars->dolar_is_first = 0;
		ft_pars_str(str, pars);
		put_env[j++] = ft_env_handler(str, env, pars);
	}
	return (ft_resizer(put_env));
}

char	*ft_env_handler(char *str, t_env *env, t_parser *parser)
{
	char	*tmp_str;
	char	*env_str;
	char	*dest;
	int		str_len;
	int		dolr_len;

	str_len = (parser->len_str[1] - parser->len_str[0] +1);
	dolr_len = (parser->len_dolar[1] - parser->len_dolar[0] +1);
	if (parser->len_str[0] == -1)
		tmp_str = ft_strdup("");
	else
		tmp_str = ft_substr(str, parser->len_str[0], str_len);
	if (parser->len_dolar[0] == -1)
		env_str = ft_strdup("");
	else
		env_str = ft_find_env(str + parser->len_dolar[0], dolr_len, env);
	if (parser->dolar_is_first)
		dest = ft_strjoin(env_str, tmp_str);
	else
		dest = ft_strjoin(tmp_str, env_str);
	free(tmp_str);
	tmp_str = NULL;
	free(env_str);
	env_str = NULL;
	return (dest);
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
