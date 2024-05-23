/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:29:21 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/05/23 18:02:22 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// "na's"im yi"l"maz  'ha"y'd'a'  patlıyor
int	ft_qutation_len_check(char *str, int len)
{
	int	i;
	int	j;
	int	check;
	int	dq;
	int	sq;
	char *tmp;

	dq = 0;
	sq = 0;
	i = -1;
	j = 0;
	check = 0;
	tmp = NULL;
	if (ft_quote_check(str, len,tmp,i,j,check,sq,dq) == 1)
		return(1);
	else if (ft_quote_check(str, len,tmp,i,j,check,sq,dq) == 2)
		return(2);
	return (0);
}

int	ft_quote_check(char *str, int len, char *tmp, int i, int j, int check, int sq, int dq)
{
	while (str[++i] && i < len)
	{
		printf("i-->%d\n",i);
		if ((str[i] == '"' && str[i + 1] != '\0')  && ((ft_squote_len(str, i) - sq) % 2 == 0
			|| ((ft_dquote_len(str,i)) > 0 && (ft_dquote_len(str,i) - dq) % 2 == 0
			&& (ft_squote_len(str, i) - sq)% 2 != 0)) && check == 0)
		{
			printf("if1\n");
			j = i;
			tmp = ft_cut_dquote(str,&i, &j,len, &check,&sq);
		}
		else if ((str[i] == '\'' && str[i + 1] != '\0')  && ((ft_dquote_len(str, i) - dq) % 2 == 0
			|| ((ft_squote_len(str,i)) > 0 && (ft_squote_len(str,i) - sq) % 2 == 0
			&& (ft_dquote_len(str, i) - dq) % 2 != 0))&& check == 0)
			tmp = ft_cut_squote(str,&i, &j,len, &check, &dq);
		else if ((str[i] == '"' && (str[i + 1] == '\0' ||  (str[i + 1] != '\0' && str[i + 1] == ' ' )))
			&& (ft_dquote_len(str,i + 1) - dq)% 2 != 0)
			return(2);
		else if ((str[i] == '\'' && (str[i + 1] == '\0' ||  (str[i + 1] != '\0' && str[i + 1] == ' ' )))
			&& (ft_squote_len(str, i + 1) - sq) % 2 != 0)
			return(1);
		if(check == 2 && ft_dquote_check(tmp, &check,dq))
			return(2);
		if (check == 1 && ft_squote_check(tmp, &check,sq))
			return(1);
	}
	return (0);
}

int ft_dquote_check(char *str, int *check, int dq)
{
	(void) dq;
	if (*check == 2 && str != NULL)
	{
		if (ft_dquote_len(str, (int)ft_strlen(str)) % 2 != 0)
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
int	ft_squote_check(char *str, int *check, int sq)
{
	(void) sq;
	if (*check == 1 && str != NULL)
	{
		printf("if-->0\n");
		printf("if_check_sq: %d\nif_check_total_sq: %d\n",sq,ft_squote_len(str , (int) ft_strlen(str)));
		if (ft_squote_len(str , (int) ft_strlen(str))% 2 != 0)
		{
			printf("if_singl--->1\n");
			free(str);
			return(1);
		}
		else
		{
			printf("if_singl--->2\n");
			free(str);
			str = NULL;
			*check = 0;
			return(0);
		}
	}
	return (0);
}
