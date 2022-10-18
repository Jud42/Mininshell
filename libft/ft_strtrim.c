/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:48:52 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/02 11:05:09 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*p;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_isset(s1[end - 1], set))
		end--;
	p = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (start < end)
		p[i++] = s1[start++];
	p[i] = '\0';
	return (p);
}
