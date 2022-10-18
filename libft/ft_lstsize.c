/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:03:01 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:58:11 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)

{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
