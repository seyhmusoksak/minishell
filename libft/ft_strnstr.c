/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:31:49 by mehmyilm          #+#    #+#             */
/*   Updated: 2023/10/29 13:38:47 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;
	char	*find;

	i = 0;
	str = (char *)haystack;
	find = (char *)needle;
	if (!find[0])
		return (str);
	while (i < len && str[i])
	{
		j = 0;
		k = i;
		while ((str[k] == find[j]) && str[k] && k < len)
		{
			k++;
			j++;
		}
		if (find[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
