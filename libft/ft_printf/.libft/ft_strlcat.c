/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:59:51 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 18:40:16 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	len_val;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	len_val = 0;
	if (dstsize > dstlen)
		len_val = srclen + dstlen;
	else
		len_val = srclen + dstsize;
	while (*src && (dstlen + 1) < dstsize)
		dst[dstlen++] = *src++;
	dst[dstlen] = '\0';
	return (len_val);
}	
