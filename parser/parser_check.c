/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/22 18:59:10 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean_str(char *str, char *clean_str,int cspace, int i, int j)
{
	printf("clean_func--->%s\n",str);
	while (str[++i])
	{
		printf("clean_i -->%d\n",i);
		if (str[i] == ' ' && cspace == 0 && ft_qutation_len_check(str, i) == 0)
		{
			clean_str[j++] = str[i];
 			while (str[i++] && str[i] == ' ')
 				cspace++;
		}
		else if (cspace > 0 && (str[i] == '"' && ((str[i - 1] != '\0' && str[i - 1] == ' ') && ft_qutation_len_check(str, i) == 0))
		 && ft_is_first(str + i, '"') == 2)
			ft_write_in_duble(str + i, clean_str, &j, &cspace,'F');
		else if (cspace > 0 && (str[i] == '\'' && (str[i - 1] == ' ' && ft_qutation_len_check(str, i) == 0))
		&& ft_is_first(str + i, '\'') == 1)
			ft_write_in_single(str + i, clean_str, &j, &cspace,'F');
		else if (str[i] != '"' && ft_qutation_len_check(str, i) == 2)
			ft_write_in_duble(str + i + 1, clean_str, &j, &cspace,'"');
		else if (str[i] != '\'' && ft_qutation_len_check(str, i) == 1)
			ft_write_in_single(str + i + 1, clean_str, &j, &cspace,'\'');
		else
			clean_str[j++] = str[i];
	}
	clean_str[++j] = '\0';
}
int ft_is_first(char *str, char keycode)
{
	int i;

	i = 0;
	if (keycode == '"')
	{
		while (str[++i])
		{
			if ((str[i] == '"' && ((str[i + 1] != '\0' && str[i + 1] == ' ') || str[i + 1] == '\0')) && ft_qutation_len_check(str, i) == 0)
				return (2);
			if (str[i] == ' ' && ft_qutation_len_check(str, i) == 0)
				break;
		}
	}
	else if (keycode == '\'')
	{
		while (str[++i])
		{
			if ((str[i] == '\'' && ((str[i + 1] != '\0' && str[i + 1] == ' ') || str[i + 1] == '\0')) && ft_qutation_len_check(str, i) == 0)
				return (1);
			if (str[i] == ' ' && ft_qutation_len_check(str, i) == 0)
				break;
		}
	}
	return (0);
}
// void	ft_clean_str(char *str, char *clean_str,int cspace, int i, int j)
// {
// 	while (str[++i])
// 	{
// 		if ((str[i] != '"') )
// 			clean_str[j++] = str[i];
// 		if (str[i] == ' ' && ft_qutation_len_check(str, i) == 0)
// 		{
// 			cspace++;
// 			while (str[i + 1] && str[i + 1] == ' ')
// 				i++;
// 		}
// 		if (((str[i] == ' ') &&  (str[i + 1] != '\0' && ((str[i + 1] == '"')
// 			|| (str[i + 1] == '\''))) && ft_qutation_len_check(str, i + 1)
// 			&& ft_first_quatiton_check(str + i +1)))
// 				clean_str[j++] = str[++i];

// 		if ((((str[i] == '\'' || str[i] == '"') && ((str[i + 1] == '\0')
// 			|| (str[i + 1] != '\0' && str[i + 1] == ' ')))
// 			&& ft_qutation_len_check(str, i) == 0)
// 			&& cspace > 0 && ft_last_quatiton_check(str, i))
// 			clean_str[j++] = str[i];
// 	}
// 	clean_str[j] = '\0';
// }

int ft_write_in_duble(char *str, char *clean_str, int *j, int *cspace, char keycode)
{
	int writed_char;

	writed_char = 0;
	printf("str_inDouble_write: %s\n",str);
	if (keycode == 'F')
		clean_str[(*j)++] = str[writed_char];
	while (str[++writed_char])
	{
		if (str[writed_char] != '"')
			clean_str[(*j)++] = str[writed_char];
		else if (((str[writed_char] == '"' && ((str[writed_char + 1] != '\0' && str[writed_char + 1] == ' ')
		|| str[writed_char + 1] == '\0')) && ft_qutation_len_check(str, writed_char + 1) == 0) && keycode == 'F')
		{
			clean_str[(*j)++] = str[writed_char];
			*cspace = 0;
			break;
		}
		writed_char++;
	}
	return (writed_char);
}
int ft_write_in_single(char *str, char *clean_str, int *j, int *cspace, char keycode)
{
	int writed_char;

	writed_char = 0;
	if (keycode == 'F')
		clean_str[(*j)++] = str[writed_char];
	while (str[++writed_char])
	{
		if (str[writed_char] != '\'')
			clean_str[(*j)++] = str[writed_char];
		else if (((str[writed_char] == '\'' && ((str[writed_char + 1] != '\0' && str[writed_char + 1] == ' ')
			|| str[writed_char + 1] == '\0')) && ft_qutation_len_check(str, writed_char + 1) == 0) && keycode == 'F')
		{
			clean_str[(*j)++] = str[writed_char];
			*cspace = 0;
			break;
		}
		writed_char++;
	}
	return (writed_char);
}
