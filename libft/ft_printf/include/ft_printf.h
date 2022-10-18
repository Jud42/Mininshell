/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:29:48 by rmamison          #+#    #+#             */
/*   Updated: 2022/04/06 12:47:25 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../libft.h"
# include <stdarg.h>
# include <stdint.h>

int	ft_printf(const char *fmt, ...);
int	ft_printchar(int c);
int	ft_printstr(char *str);
int	ft_printptr(unsigned long long ptr);
int	ft_print_d(int a);
int	ft_print_u(unsigned int a);
int	ft_print_x(unsigned int nb, const char fmt);

#endif
