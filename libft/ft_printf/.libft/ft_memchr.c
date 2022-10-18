/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:56:13 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 18:47:49 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	size_t			i;

	i = 0;
	while (i < n)
	{
		ps = (unsigned char *) s;
		if (ps[i] == (unsigned char) c)
			return ((void *) &ps[i]);
		i++;
	}
	return (NULL);
}
