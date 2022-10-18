/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:05:34 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/17 20:01:30 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	counthexa(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		i++;
		nb /= 16;
	}
	return (i);
}

static void	put_hexa(unsigned int nb, const char fmt)
{
	if (nb >= 16)
	{
		put_hexa(nb / 16, fmt);
		put_hexa(nb % 16, fmt);
	}
	else
	{
		if (nb <= 9)
			ft_printchar(nb + '0');
		else
		{
			if (fmt == 'x')
				ft_printchar((nb - 10) + 'a');
			if (fmt == 'X')
				ft_printchar((nb - 10) + 'A');
		}
	}
}

int	ft_print_x(unsigned int nb, const char fmt)
{
	if (nb == 0)
		return (ft_printchar('0'));
	else
		put_hexa(nb, fmt);
	return (counthexa(nb));
}
