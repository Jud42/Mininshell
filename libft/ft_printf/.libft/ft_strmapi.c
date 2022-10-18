/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:51:48 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/02 19:52:42 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char			*ps;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	ps = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ps)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ps[i] = f(i, s[i]);
		i++;
	}
	ps[i] = '\0';
	return (ps);
}
