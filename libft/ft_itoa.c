/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:53:10 by rmamison          #+#    #+#             */
/*   Updated: 2022/04/09 10:51:13 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int nb)
{
	int	i;

	i = 0;
	if (nb < 0 || nb == 0)
		i = 1;
	while (nb != 0)
	{
		i++;
		nb /= 10;
	}	
	return (i);
}

static void	convnbr(long nb, char *str, int *i)
{
	if (nb > 9)
	{
		convnbr(nb / 10, str, i);
		convnbr(nb % 10, str, i);
	}
	else
		str[(*i)++] = nb + '0';
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*str;

	nb = n;
	str = (char *)malloc(sizeof(char) * (count(n) + 1));
	if (!str)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	i = 0;
	if (nb < 0)
	{	
		str[i++] = '-';
		nb *= -1;
	}
	convnbr(nb, str, &i);
	str[i] = '\0';
	return (str);
}
