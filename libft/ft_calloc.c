/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:46:55 by rmamison          #+#    #+#             */
/*   Updated: 2022/04/21 20:07:16 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int	*p;

	p = malloc (count * size);
	if (p)
		ft_bzero (p, (count * size));
	if (count == 0 || size == 0)
		count = 0;
	return (p);
}
