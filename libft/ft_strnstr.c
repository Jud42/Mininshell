/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:34:05 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/04 12:02:17 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	size_t	j;

	if (*substr == 0)
		return ((char *) str);
	i = 0;
	j = 0;
	while (str[i] && i < len)
	{
		while ((str[i] == substr[j] || substr[j] == '\0') && i < len)
		{
			i++;
			j++;
			if (substr[j] == '\0')
				return ((char *)&str[i - j]);
		}
		i++;
	}
	return (NULL);
}
