/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:13:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/12 18:08:21 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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



