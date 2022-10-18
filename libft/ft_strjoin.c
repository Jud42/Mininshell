/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:06:02 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/02 20:16:15 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len_s1;
	size_t	len_all;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1) + 1;
	len_all = len_s1 + ft_strlen(s2);
	p = malloc (sizeof(char) * len_all);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, len_s1);
	ft_strlcat(p, s2, len_all);
	return (p);
}
