/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:13:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/06/28 19:10:45 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_pipe_split(char *line)
{
    char **src;
    char ** tmp;
    
    if (line[0] == "|" || line[ft_strlen(line) - 1] == "|")
      return NULL;
    src = ft_split(line, "|");
    tmp = ft_quote_control(src, pipe_counter(src));
    

    
}

char **ft_quote_control(char **src, int pipe_counter)
{
    
    int chech1;
    int chechk2;
    char **tmp;

    tmp = (char **)malloc(sizeof(char *) * pipe_counter);
}

int pipe_counter(char **line)
{
    int i;
    int count;
    //char *dst;
    
    i = 0;
    count = 1;
    




    
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
    return (count);
}




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
int	ft_double_str_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}



