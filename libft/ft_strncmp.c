/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:57:59 by rmamison          #+#    #+#             */
/*   Updated: 2022/07/21 11:10:22 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (1);
	while (n--)
	{
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)(s2 - 1));
		if (*s1++ == '\0')
			return (0);
	}
	return (0);
}	
