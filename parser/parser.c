/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:01 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/11 16:39:00 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_parser(t_state *state)
{
	t_parser *tmp_pars;
	int i;
	int j;
	char **argv;
	i = 0;
	j = 0;
	if (ft_arg_check(ft_strtrim(state->line, " ")))
		exit(1); // freelenecek
	// argv = ft_mustafa_fonksiyonu()
	argv = ft_split(ft_strtrim(state->line, ' '), '|'); //gecici olarak koydum musti kodu yazdığında eklicem
	ft_clean_quatition(argv);
}
void	ft_clean_quatition(char **str)
{
	
}
// int ft_count(t_parser *pars, char *str)
// {

// 	int	check;
// 	int	i;

// 	i = 0;
// 	check = 1;
// 	while (str[i])
// 	{
// 		if (ft_isalpha(str[i]) && check == 1)
// 		{
// 			pars->count_comnd++;
// 			check = 0;
// 		}
// 		else if ((str[i] == '"' || str[i] == '\'') && str[i] == '-')
// 			pars->flag_count++;
// 		else
// 		{
// 			if (str[i] == '-')
// 			{
// 				pars->flag_count++;
// 				check = 0;
// 			}
// 			else if (str[i] == '<' || str[i] == '>' || str[i] )
// 				pars->op_count++;
// 			else if (!(str[i] > 8 && str[i] < 12) && str[i] !=  ' ')
// 				pars->arg_count++;
// 			if (ft_mini_counter(pars, str, check))
// 				return (1);
// 		}
// 		i++;
// 	}
// }
// void	ft_mini_counter(t_parser *pars,char *str, int check)
// {
// 	int	i;

// 	i = 1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '<'  || str[i] == '>')
// 		{
// 			pars->flag_count++;
// 			check = 1;
// 		}
// 		else if (check == 1)
// 			pars->arg_count++;
// 	}
// }

void	ft_clean_arg(char **str)
{
	int	i;
	int	j;

	while (str[i])
	{
		while (str[j])
		{

		}
	}
}
char	*ft_double_to_one(char **src)
{
	int i;
	char	*dest;

	i = -1;
	while (src[++i])
		dest = ft_strjoin(dest, src[i]);
	return(dest);
}

