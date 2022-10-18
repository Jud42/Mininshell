/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:36:22 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/17 19:58:29 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0 || nb < 0)
		i = 1;
	while (nb != 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

static char	*uitoa(unsigned int n)
{
	char	*p;
	int		len;

	len = count(n);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	p[len] = '\0';
	while (n != 0)
	{
		p[len - 1] = n % 10 + 48;
		n /= 10;
		len--;
	}
	return (p);
}

int	ft_print_u(unsigned int a)
{
	int		larg_print;
	char	*p;

	larg_print = 0;
	if (a == 0)
		larg_print += write(1, "0", 1);
	else
	{
		p = uitoa(a);
		larg_print += ft_printstr(p);
		free(p);
	}
	return (larg_print);
}
