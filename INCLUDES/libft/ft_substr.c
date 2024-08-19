/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:23:19 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/08/14 14:19:20 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ns;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	ns = malloc(sizeof(char) * (len + 1));
	if (ns == NULL)
		return (NULL);
	while (s[start] && len > 0)
	{
		ns[i] = *(char *)(s + start);
		i++;
		start++;
		len--;
	}
	ns[i] = '\0';
	return (ns);
}
