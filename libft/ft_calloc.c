/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:37:20 by mehmyilm          #+#    #+#             */
/*   Updated: 2023/10/18 16:24:25 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len;
	void	*at;

	len = count * size;
	at = malloc(len);
	if (at == NULL)
		return (NULL);
	ft_bzero(at, len);
	return (at);
}
