/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 09:48:34 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 18:34:04 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	int		s_ln;

	s_ln = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((int)start >= s_ln)
		return (ft_strdup(""));
	if (s_ln - (int)start < (int)len)
		len = s_ln - (int)start;
	p = (char *)malloc((len + 1) * sizeof(*s));
	if (!p)
		return (NULL);
	i = 0;
	while (len--)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
