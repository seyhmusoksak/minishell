/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:49:22 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/01/29 16:44:53 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	count;
	char	*cs;

	i = 0;
	count = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
		{
			cs = (char *) s + i;
			count = 1;
		}
		i++;
	}
	if (count > 0)
		return (cs);
	return (0);
}
