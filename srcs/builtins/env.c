/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:07:01 by mnikolov          #+#    #+#             */
/*   Updated: 2022/08/15 11:39:42 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_lst *ms)
{
	t_env	*tmp;
	char	*value;

	tmp = ms->env;
	while (tmp != NULL)
	{
		value = ft_strchr(tmp->value, '=');
		if (value != NULL)
		{
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
}
