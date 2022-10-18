/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:57:59 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 18:47:23 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	while (n--)
	{
		cs1 = (unsigned char *) s1++;
		cs2 = (unsigned char *) s2++;
		if (*cs1 != *cs2)
			return (*cs1 - *cs2);
		if (*cs1 == '\0')
			return (0);
	}
	return (0);
}	
