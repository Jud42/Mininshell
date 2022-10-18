/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:30:39 by rmamison          #+#    #+#             */
/*   Updated: 2021/11/17 19:56:54 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_d(int a)
{
	int		len_str;
	char	*p;

	p = ft_itoa(a);
	len_str = ft_strlen(p);
	ft_putstr_fd(p, 1);
	free(p);
	return (len_str);
}
