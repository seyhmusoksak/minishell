/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:23:30 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/10 21:01:28 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_env(char **str, t_state *state)
{
	t_env		*env;
	// t_parser	*parser;
	char		**dest;
	int			i;

		printf("i: %d\n", (ft_double_str_len(str)));
	dest = malloc(sizeof(char *) * (ft_double_str_len(str) + 1));
	if (!dest)
		return (NULL);
	dest[ft_double_str_len(str)] = NULL;
	// parser = state->pars;
	i = -1;
	while (str[++i])
	{
		env = state->env;
		if (ft_is_dolar(str[i]))
		{
			dest[i] = ft_dolar_handler(str[i], env);
		}
		else
			dest[i] = ft_strdup(str[i]);
	}
	printf("---------------------------------------------\n");
	return(dest);
}
int	ft_is_dolar(char *str)
{
	int	i;

	if (str[0] != '\'' && str[ft_strlen(str) -1] != '\''
		&& ft_strchr(str, '$') != NULL && ft_strlen(str) > 1)
	{
		i = 0;
		while (str[i] != '$')
			i++;
		if (str[i +1] != '\0' && str[i +1] != ' ')
			return (1);
	}
	return (0);
}
char	* ft_dolar_handler(char *str, t_env *env)
{
	char	*tmp;
	char	*dest;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (str[i] != '$')
		i++;
	start = ++i;
	tmp = malloc(sizeof(char) * start);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, start);
	while (str[i] != '\0')
		i++;
	end = i;
	dest = ft_strjoin(tmp, ft_find_env(str + start, end, env));
	free(tmp);
	return (dest);
}

char	*ft_find_env(char *str, int n, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(str, env->key, n) == 0)
		{
			printf("BULUNAN: env->value: %s\n", env->value);
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}
