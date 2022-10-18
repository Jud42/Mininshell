/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:19:56 by rmamison          #+#    #+#             */
/*   Updated: 2022/05/24 20:56:45 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	count_nbr(uintptr_t num)
{
	int	i;

	i = 0;
	while (num)
	{
		i++;
		num /= 16;
	}
	return (i);
}

static void	put_nbr(uintptr_t num)
{
	if (num >= 16)
	{
		put_nbr(num / 16);
		put_nbr(num % 16);
	}
	else
	{	
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10) + 'a', 1);
	}
}

int	ft_printptr(unsigned long long ptr)
{
	int	larg_print;

	larg_print = 0;
	larg_print += write(1, "0x", 2);
	if (ptr == 0)
		larg_print += write(1, "0", 1);
	else
	{
		put_nbr(ptr);
		larg_print += count_nbr(ptr);
	}
	return (larg_print);
}
