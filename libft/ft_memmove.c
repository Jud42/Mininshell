/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:55:26 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 18:45:26 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*pdst;
	const char	*psrc;

	pdst = dst;
	psrc = src;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
	{
		while (n--)
			pdst[n] = psrc[n];
	}
	else
	{
		while (n--)
			*pdst++ = *psrc++;
	}
	return (dst);
}
