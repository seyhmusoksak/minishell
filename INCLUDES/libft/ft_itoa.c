/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:58:10 by mehmyilm          #+#    #+#             */
/*   Updated: 2023/10/23 14:29:01 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long nb)
{
	long	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	long	len;
	char	*str;

	nb = (long )n;
	len = ft_len(nb);
	if (nb == 0)
		return (ft_strdup("0"));
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		str[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	str[ft_len(n)] = '\0';
	return (str);
}
