/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:28:21 by mehmyilm          #+#    #+#             */
/*   Updated: 2023/10/19 11:30:43 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;

	cs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)cs[i] == (unsigned char)c)
			return (&cs[i]);
		i++;
	}
	return (NULL);
}
