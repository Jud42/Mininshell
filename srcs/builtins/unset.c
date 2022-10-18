/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:08 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/11 11:44:22 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_var(char *str, t_env **cur)
{	
	t_env	*new;

	while (*cur)
	{
		new = (*cur)->next;
		if (new)
		{
			if (!ft_strncmp(new->value, str, ft_strlen(str)))
			{
				(*cur)->next = new->next;
				free(new->value);
				free(new);
				new = NULL;
				return (1);
			}
		}
		*cur = (*cur)->next;
	}
	return (0);
}

void	ft_unset(char *str, t_lst *ms)
{
	t_env	*cur;

	cur = ms->env;
	if (!ft_strncmp(cur->value, str, ft_strlen(str)))
	{
		ms->env = ms->env->next;
		free(cur->value);
		free(cur);
		cur = NULL;
		ms->n_env--;
		return ;
	}
	else if (find_var(str, &cur))
		ms->n_env--;
}
