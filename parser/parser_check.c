/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 01:07:17 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/25 17:26:40 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// "ec"ho"" "me'"m"o" 'nas"i''m'
void	ft_clean_str(char *str, char *clean_str,int cspace, int i, int j)
{
	printf("clean_func--->%s\n",str);
	while (str[++i])
	{
		printf("i->%d\n",i);
		if (str[i] == ' ' && cspace == 0 && ft_quote_len_check(str, i) == 0)
		{
			printf("if0-->%c\n",str[i]);
			clean_str[j++] = str[i];
 			while (str[i++] && str[i] == ' ')
 				cspace++;
			printf("if1-->%c\n",str[i]);
		}
		else if (cspace > 0 && (str[i] == '"' && ((str[i - 1] != '\0' && str[i - 1] == ' ') && ft_quote_len_check(str, i) == 0))
		 && ft_is_first(str + i, '"') == 2)
		 {
			printf("if2-->%c\n",str[i]);
			ft_write_in_duble(str + i, clean_str, &j, &cspace,'F');
		 }
		else if (cspace > 0 && (str[i] == '\'' && (str[i - 1] == ' ' && ft_quote_len_check(str, i) == 0)) //quote_len fonksiyonundan 0 donuyor çunku i ye kadar baksın diyorsun ama tırnaktan sonrası nul değil
		&& ft_is_first(str + i, '\'') == 1)
		{
			printf("if3-->%c\n",str[i]);
			ft_write_in_single(str + i, clean_str, &j, &cspace,'F');
		}
		else if (str[i] == '"' && ft_quote_len_check(str, i + 1) == 2)
		{
			printf("if4-->%c\n",str[i]);
			ft_write_in_duble(str + i, clean_str, &j, &cspace,'"');
			printf("clean_str->>>>>%s\n",clean_str);
		}
		else if (str[i] == '\'' && ft_quote_len_check(str, i + 1) == 1)
		{
			printf("if5-->%c\n",str[i]);
			ft_write_in_single(str + i, clean_str, &j, &cspace,'\'');
		}
		else
		{
			printf("if6-->%c\n",str[i]);
			clean_str[j++] = str[i];
		}
		printf("len->%d\n",ft_quote_len_check(str, i + 1));
	}
	clean_str[++j] = '\0';
}
int ft_is_first(char *str, char keycode)
{
	int i;

	i = 0;
	printf("ft_first->%s, %c",str,keycode);
	if (keycode == '"')
	{
		while (str[++i])
		{
			if ((str[i] == '"' && ((str[i + 1] != '\0' && str[i + 1] == ' ') || str[i + 1] == '\0')) && ft_quote_len_check(str, i + 1) == 0)
				return (2);
			if (str[i] == ' ' && ft_quote_len_check(str, i) == 0)
				break;
		}
	}
	else if (keycode == '\'')
	{
		while (str[++i])
		{
			if ((str[i] == '\'' && ((str[i + 1] != '\0' && str[i + 1] == ' ') || str[i + 1] == '\0')) && ft_quote_len_check(str, i + 1) == 0)
				return (1);
			if (str[i] == ' ' && ft_quote_len_check(str, i) == 0)
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
// 		if (str[i] == ' ' && ft_quote_len_check(str, i) == 0)
// 		{
// 			cspace++;
// 			while (str[i + 1] && str[i + 1] == ' ')
// 				i++;
// 		}
// 		if (((str[i] == ' ') &&  (str[i + 1] != '\0' && ((str[i + 1] == '"')
// 			|| (str[i + 1] == '\''))) && ft_quote_len_check(str, i + 1)
// 			&& ft_first_quatiton_check(str + i +1)))
// 				clean_str[j++] = str[++i];

// 		if ((((str[i] == '\'' || str[i] == '"') && ((str[i + 1] == '\0')
// 			|| (str[i + 1] != '\0' && str[i + 1] == ' ')))
// 			&& ft_quote_len_check(str, i) == 0)
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
		|| str[writed_char + 1] == '\0')) && ft_quote_len_check(str, writed_char + 1) == 0) && keycode == 'F' && cspace > 0)
		{
			clean_str[(*j)++] = str[writed_char];
			*cspace = 0;
			break;
		}
		else if (str[writed_char] == ' ' && ft_quote_len_check(str, writed_char) == 0)
			break ;
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
			|| str[writed_char + 1] == '\0')) && ft_quote_len_check(str, writed_char + 1) == 0) && keycode == 'F')
		{
			clean_str[(*j)++] = str[writed_char];
			*cspace = 0;
			break;
		}
		else if (str[writed_char] == ' ' && ft_quote_len_check(str, writed_char) == 0)
			break ;
	}
	return (writed_char);
}

