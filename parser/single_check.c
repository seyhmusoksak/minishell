/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:54:48 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/18 01:08:11 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_qutation_len_check(char *str, int len)
{
	int	i;
	int	j;
	int	check;
	char *tmp;

	i = -1;
	j = 0;
	check = 0;
	tmp = NULL;
	if (ft_double_single_quatition(str, len,tmp,i,j,check) == 1)
		return(1);
	else if (ft_double_single_quatition(str, len,tmp,i,j,check) == 2)
		return(2);
	return (0);
}

char *ft_cut_singl_quat(char *str, int *i, int *j, int len, int *check)
{
	char	*tmp;

	tmp = NULL;
	*j = *i;
	while (str[++(*j)] && *j < len)
	{
		if ((str[*j] == '\'' ||  str[(*j)+1] == '\0') && *check == 0)
		{
			tmp = ft_substr(str, *i, (*j - *i) + 1);
			// printf("single tmp ->%s\n",tmp);
			*check = 1;
			*i = *j;
			break;
		}
	}
	return(tmp);
}

int	ft_singl_quat_check(char *str, int *check)
{
	if (*check == 1 && str != NULL)
	{
		// printf("if-->0\n");
		if (ft_single_len(str , (int) ft_strlen(str)) % 2 != 0)
		{
			// printf("if_singl--->1\n");
			free(str);
			return(1);
		}
		else
		{
			// printf("if_singl--->2\n");
			free(str);
			str = NULL;
			*check = 0;
			return(0);
		}
	}
	return (0);
}
int	ft_single_len(char *str, int len)
{
	int	i;
	int	singl;

	singl = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'')
			singl++;
		i++;
	}
	return(singl);
}

// int	ft_single_quatition(char *str, int len)
// {
// 	int	i;
// 	int	j;
// 	int	check;
// 	char *tmp;

// 	i = -1;
// 	check = 0;
// 	tmp = NULL;
// 	while (str[++i] && i < len)
// 	{
// 		printf("singl i: %d\n",i);
// 		if ((str[i] == '\'' && str[i + 1] != '\0')  && (ft_double_len(str, i) % 2 == 0
// 			|| ((ft_single_len(str,i)) > 0 && ft_single_len(str,i) % 2 == 0
// 			&& ft_double_len(str, i) % 2 != 0)))
// 		{
// 			j = i;
// 			tmp = ft_cut_singl_quat(str,&i, &j,len, &check);
// 		}
// 		else if ((str[i] == '\'' && (str[i + 1] == '\0' || str[i + 1] == ' '))
// 			&& ft_single_len(str, i + 1) % 2 != 0)
// 			return(1);
// 		if(ft_singl_quat_check(tmp, &check))
// 			return(1);
// 	}
// 	return (0);
// }
