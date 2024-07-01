/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:13:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/01 21:50:23 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_pipe_split(char *line)
{
	char	**src;
	char	**tmp;
	int		i;
	int		pc;

	pc = (pipe_c(line) + 1);
	i = 0;
	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
		return (NULL);
	src = ft_split(line, '|');
	tmp = (char **)malloc(sizeof(char *) * (pc + 1));
	if (!tmp)
	{
		ft_free_double_str(src);
		return (NULL);
	}
	tmp[pc] = NULL;
	ft_quote_control(src, tmp, 0);
	ft_free_double_str(src);
	return (tmp);
}

void	ft_quote_control(char **src, char **tmp, int j)
{
	char	*dst;
	bool	check;
	int		i;

	i = 0;
	check = false;
	while (src[i] != NULL)
	{
		if (!check)
		{
			dst = ft_strdup(src[i]);
			check = true;
		}
		if (ft_quote_len_check(dst, ft_strlen(dst)) != 0 )
		{
			ft_strjoin_and_free(&dst, src[++i]);
			printf("haciiiii: %s\n", dst);

		}
		if (ft_quote_len_check(dst, ft_strlen(dst)) == 0 && dst != NULL)
		{
			tmp[j] = ft_strdup(dst);
			check = false;
			j++;
		}
		++i;
	}
	tmp[j] = NULL;
}

int	pipe_c(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(line) && line[i] != '\0')
	{
		if (line[i] == '|' && ft_quote_len_check(line, i) == 0)
			count++;
		else if (line[i] == '|' && ft_quote_len_check(line, i) != 0)
		{
			while (line[++i])
			{
				if ((line[i] == '|' || line[i + 1] == '\0')
					&& ft_quote_len_check(line, i) == 0)
				{
					count++;
					break ;
				}
			}
		}
		i++;
	}
	return (count);
}

void	ft_strjoin_and_free(char **dst, char *s2)
{
	char	*result;
	char	*tmp;

	if (!*dst || !s2)
		return ;
	tmp = ft_strjoin(*dst, "|");
	result = ft_strjoin(tmp, s2);
	free(tmp);
	free(*dst);
	*dst = NULL;
	*dst = ft_strdup(result);
	printf("func içi: %s\n", *dst);
	free(result);
	return ;
}


// char	*line_copy(char *line, int i)
// {
// 	int		j;
// 	char	*src;

// 	j = 0;
// 	src = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
// 	if (src == NULL)
// 		return (NULL);
// 	while (line[i])
// 	{
// 		src[j] = line[i];
// 		j++;
// 		i++;
// 	}
// 	src[j] = '\0';
// 	return (src);
// }




	//if (ft_quote_len_check(line[0], ft_strlen(line[0])) != 0)
		// dst = line[0];
	// while (line[i])
	// {
	//     if (i == 0)
	//     {
	//         dst = line[i];
	//         i++;
	//         if (ft_quote_len_check(line[i], ft_strlen(line[i])) != 0)
	//             free(line[i]);
	//     }
	//     else if (ft_quote_len_check(line[i], ft_strlen(line[i])) != 0)
	//     {
	//         line[i - 1] =
	//         i++;
	//     }
	//     else if (i != 0 && ft_quote_len_check(dst, ft_strlen(dst)) == 0)
	//     {
	//         count++;
	//     }
	//     else
	//         i++;
	// }




// echo "musta|fa"na'b|'er | bebe
// src[0]= echo "musta|
// src[0]= fa"na'b
// src[0]= 'er
// src[0]= bebe

//dst = echo "musta| fa"na'b


// tmp[0]= fa"na'b
// tmp[0]= 'er
// tmp[0]= bebe


// char	**ft_pipe_split(char *line)
// {
// 	int			i;
// 	char		**str;
// 	char		**tmp;

// 	i = 0;
// 	str = ft_split(line, '|');
// 	// if (str[1] == NULL)
// 	// {
// 	// 	ft_free_double_str(str);
// 	// 	ft_error_mesage("Error : Enter a value after the | sign");
// 	// 	return(0);
// 	// }
// 	while (str[i])
// 	{
// 		if (str[i + 1] && ft_quote_len_check(str[i], (int) ft_strlen(str[i]))
// 			&& ft_quote_len_check(str[i + 1], (int) ft_strlen(str[i + 1])))
// 		{
// 			tmp = ft_pipe_join(str);
// 			str = NULL;
// 			str = tmp;
// 			free(tmp);
// 		}
// 		i++;
// 	}
// 	return (str);
// }
// char	**ft_pipe_join(char **str)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = ft_strjoin(str[i], "|");
// 	free(str[i]);
// 	str[i] = tmp;
// 	tmp = NULL;
// 	tmp = ft_strjoin(str[i], str[i + 1]);
// 	free(str[i]);
// 	free(str[i + 1]);
// 	str[i + 1] = NULL;
// 	str[i] = tmp;
// 	return (str);
// }

// echo "musta|fa"na'b|'er | bebe
// src[0]= echo "musta|
// src[0]= fa"na'b
// src[0]= 'er
// src[0]= bebe

//dst = echo "musta| fa"na'b


// tmp[0]= fa"na'b
// tmp[0]= 'er
// tmp[0]= bebe
/*
	tmp ilk src 0
	if (tmp dengesiz ise) tmp



*/



// int	pipe__c(char *line, int i, int count, char *tmp, char *dst)
// {
// 	tmp = line;
// 	while (tmp[++i])
// 	{
// 		if (tmp[i] == "|" && ft_quote_len_check(tmp, i) == 0)
// 			count++;
// 		else if (tmp[i] == "|" && ft_quote_len_check(tmp, i) != 0)
// 		{
// 			while (tmp[++i])
// 			{
// 				if (tmp[i] == "|" && ft_quote_len_check(tmp, i) == 0)
// 				{
// 					dst = line_copy(tmp, i);
// 					free(tmp);
// 					tmp = dst;
// 					free(dst);
// 					count++;
// 					break ;
// 				}
// 			}
// 			i--;
// 		}
// 	}
// 	free(tmp);
// 	free(dst);
// 	return (count);
// }
