/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:01 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/08 19:23:55 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_parser(t_state *state)
{
	t_parser *tmp_pars;
	int i;
	int j;
	char **argv;

	argv = ft_split(ft_strtrim(state->line, ' '), ' ');
	i = 0;
	j = 0;
	tmp_pars = state->pars;
	while (tmp_pars)
	{
		ft_count(tmp_pars, argv[i]);
	}
}

int ft_count(t_parser *pars, char *str)
{
	int i;
	int	check;

	check = 0;
	i = 1;
	if (str[0] != '<')
		pars->count_comnd++;
	else if ((str[1] == '"' || str[1] == '\'') && str[1] == '-')
		pars->flag_count++;
	else
	{
		if (str[i] == '-')
		{
			pars->flag_count++;
			check = 0;
		}
		else if (str[i][0] == '<' || str[i][0] == '>' || str[i][0] == '|')
			pars->op_count++;
		else
			pars->arg_count++;
		if (ft_mini_counter(pars, str[i], check))
			return (1);
	}
}

// void    ft_get_line(t_state *state)
// {
//     int i;
//     int j;
//     char **argv_line;
//     t_parser *tmp_pars;

//     tmp_pars = state->pars;
//     i = 1;
//     j = 0;
//     argv_line = ft_split(ft_strtrim(state->line," "), ' ');
//     while (argv_line[i])
//     {
//         state->pars->flag_count = 0;
//         state->pars->arg_count = 0;
//         state->pars->op_count = 0;
//         if (ft_flag_counter(argv_line, state->pars));

//         ft_init_data(state, argv_line);
//     }
// }
// int ft_flag_counter(char **str,t_parser *pars)
// {
//     int i;
//     int check;

//     check = 1;
//     i = 1;
//     while (str[i])
//     {
//         if ((str[i][0] == '"' || str[i][0] == '\'') && str[i][1] == '-')
//             pars->flag_count++;
//         else
//         {
//             if (str[i][0] == '-')
//             {
//                 pars->flag_count++;
//                 check = 0;
//             }
//             else if (str[i][0] == '<'  || str[i][0] == '>' || str[i][0] == '|')
//                 pars->op_count++;
//             else
//                 pars->arg_count++;
//             if (ft_mini_counter(pars,str[i], check))
//                 return (1);
//         }
//         i++;
//     }
//     return(0);
// }

// int ft_mini_counter(t_parser *pars, char *str, int check)
// {
//     int j;

//     j = 1;
//     if (str[0] == '|')
//         return (1);
//     while (str[j])
//     {
//         if (str[j] == '<'  || str[j] == '>' || str[j] == '|')
//         {
//             if (str[j] == '|')
//                 pars->count_comnd++;
//             pars->flag_count++;
//             check = 1;
//         }
//         else if (check == 1)
//         {
//             pars->arg_count++;
//             check = 0;
//         }
//         j++;
//     }
//     return (0);
// }
// void    ft_init_data(t_parser *pars, char **str)
// {

//     if (pars->flag_count)
//         pars->flag = malloc(sizeof(char *) * pars->flag_count);
//     if (pars->arg_count)
//         pars->arg = malloc(sizeof(char *) * pars->arg_count);
//     if (pars->op_count)
//         pars->operator = malloc(sizeof(char *) * pars->op_count);
//     if (!pars->flag || !pars->arg || pars->operator)
//         exit(1); //freeleme ya da error mesajı eklenmeli taslak olarak bıraktım

// }
