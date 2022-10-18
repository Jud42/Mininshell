/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:00:08 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 18:38:57 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		slen;

	slen = ft_strlen(s1);
	p = malloc(slen + 1);
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, slen);
	p[slen] = '\0';
	return (p);
}
