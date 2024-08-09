/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:14:38 by mehmyilm          #+#    #+#             */
/*   Updated: 2023/10/17 11:34:13 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cs;
	size_t			i;

	i = 0;
	cs = (unsigned char *)s;
	while (i < n)
	{
		cs [i] = 0;
		i++;
	}
}
