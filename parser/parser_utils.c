/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:13:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/06/28 15:03:52 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_pipe_split(char *line)
{
	int			i;
	char		**str;
	char		**tmp;

	i = 0;
	str = ft_split(line, '|');
	// if (str[1] == NULL)
	// {
	// 	ft_free_double_str(str);
	// 	ft_error_mesage("Error : Enter a value after the | sign");
	// 	return(0);
	// }
	while (str[i])
	{
		if (str[i + 1] && ft_quote_len_check(str[i], (int) ft_strlen(str[i]))
			&& ft_quote_len_check(str[i + 1], (int) ft_strlen(str[i + 1])))
		{
			tmp = ft_pipe_join(str);
			str = NULL;
			str = tmp;
			free(tmp);
		}
		i++;
	}
	return (str);
}
char	**ft_pipe_join(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(str[i], "|");
	free(str[i]);
	str[i] = tmp;
	tmp = NULL;
	tmp = ft_strjoin(str[i], str[i + 1]);
	free(str[i]);
	free(str[i + 1]);
	str[i + 1] = NULL;
	str[i] = tmp;
	return (str);
}
int	ft_double_str_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}



