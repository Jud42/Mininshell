/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:29 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/17 20:29:59 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	handle_format(va_list args, const char *fmt)
{
	int	larg_print;

	larg_print = 0;
	if (*fmt == '%')
		larg_print += ft_printchar('%');
	else if (*fmt == 'c')
		larg_print += ft_printchar(va_arg(args, int));
	else if (*fmt == 's')
		larg_print += ft_printstr(va_arg(args, char *));
	else if (*fmt == 'p')
		larg_print += ft_printptr(va_arg(args, unsigned long long));
	else if (*fmt == 'd' || *fmt == 'i')
		larg_print += ft_print_d(va_arg(args, int));
	else if (*fmt == 'u')
		larg_print += ft_print_u(va_arg(args, unsigned int));
	else
		if (*fmt == 'x' || *fmt == 'X')
			larg_print += ft_print_x(va_arg(args, unsigned int), *fmt);
	return (larg_print);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		larg_print;

	larg_print = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{	
			larg_print += handle_format(args, &(*(fmt + 1)));
			fmt++;
		}
		else
			larg_print += ft_printchar(*fmt);
		fmt++;
	}
	va_end(args);
	return (larg_print);
}
