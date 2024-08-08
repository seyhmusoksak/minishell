/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:32:40 by mehmyilm          #+#    #+#             */
/*   Updated: 2023/10/29 13:31:04 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lens1;
	char	*dst;

	lens1 = ft_strlen(s1);
	i = -1;
	dst = malloc(sizeof(char) * (lens1 + ft_strlen(s2) + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[++i])
		dst[i] = (char )s1[i];
	i = -1;
	while (s2[++i])
	{
		dst[lens1] = s2[i];
		lens1++;
	}
	dst[lens1] = '\0';
	return (dst);
}
