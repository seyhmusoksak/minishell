/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:54:48 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/18 01:40:52 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_double_single_quatition(char *str, int len, char *tmp, int i, int j, int check)
{
	while (str[++i] && i < len)
	{
		printf("i-->%d\n",i);
		if ((str[i] == '"' && str[i + 1] != '\0')  && (ft_single_len(str, i) % 2 == 0
			|| ((ft_double_len(str,i)) > 0 && ft_double_len(str,i) % 2 == 0
			&& ft_single_len(str, i) % 2 != 0)) &&check == 0)
		{
			j = i;
			tmp = ft_cut_double_quat(str,&i, &j,len, &check);
		}
		else if ((str[i] == '\'' && str[i + 1] != '\0')  && (ft_double_len(str, i) % 2 == 0
			|| ((ft_single_len(str,i)) > 0 && ft_single_len(str,i) % 2 == 0
			&& ft_double_len(str, i) % 2 != 0))&& check == 0)
			tmp = ft_cut_singl_quat(str,&i, &j,len, &check);
		else if ((str[i] == '"' && (str[i + 1] == '\0' ||  (str[i + 1] != '\0' && str[i + 1] == ' ' )))
			&& ft_double_len(str,i + 1) % 2 != 0)
			return(2);
		else if ((str[i] == '\'' && (str[i + 1] == '\0' ||  (str[i + 1] != '\0' && str[i + 1] == ' ' )))
			&& ft_single_len(str, i + 1) % 2 != 0)
			return(1);
		if(check == 2 && ft_double_quat_check(tmp, &check))
			return(2);
		if (check == 1 && ft_singl_quat_check(tmp, &check))
			return(1);
	}
	return (0);
}


char *ft_cut_double_quat(char *str, int *i, int *j, int len, int *check)
{
	char *tmp;

	tmp = NULL;
	while (str[++(*j)] && *j < len)
	{
		if ((str[*j] == '"' || str[(*j) + 1] == '\0') && *check == 0)
		{
			tmp = ft_substr(str, *i, (*j - *i) + 1);
			*check = 2;
			*i = *j;
			// printf("dbl_cut_tmp:%s\n",tmp);;
			// printf("dbl_i: %d\ndbl_j: %d\n",*i,*j);
			break;
		}
	}
	return (tmp);
}

int ft_double_quat_check(char *str, int *check)
{
	if (*check == 2 && str != NULL)
	{
		if (ft_double_len(str, (int)ft_strlen(str)) % 2 != 0)
		{
			free(str);
			return (1);
		}
		else
		{
			free(str);
			*check = 0;
			return (0);
		}
	}
	return (0);
}
int ft_double_len(char *str, int len)
{
	int i;
	int dbl;

	dbl = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '"')
			dbl++;
		i++;
	}
	return (dbl);
}
