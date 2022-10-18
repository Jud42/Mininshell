/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:55:26 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 18:46:20 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pb;
	size_t			i;

	pb = b;
	i = 0;
	while (i < len)
	{
		pb[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
