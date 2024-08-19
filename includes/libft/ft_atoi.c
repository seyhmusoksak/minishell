/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:52:20 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/01/29 16:40:04 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char	*cstr;
	int		i;
	int		sign;
	int		num;

	i = 0;
	num = 0;
	sign = 1;
	cstr = (char *)str;
	while ((cstr[i] >= 9 && cstr[i] <= 13) || cstr[i] == ' ')
		i++;
	if (cstr[i] == '-' || cstr[i] == '+')
	{
		if (cstr[i] == '-')
			sign *= -1;
		i++;
	}
	while (cstr[i] >= '0' && cstr[i] <= '9')
	{
		num = ((num * 10) + cstr[i] - '0');
		i++;
	}
	return (sign * num);
}
