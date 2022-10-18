/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:04:32 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/18 15:12:28 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_redir(t_redir *node)
{
	t_redir	*temp;	
	t_redir	*old;	

	old = NULL;
	temp = NULL;
	if (!node)
		return ;
	temp = node;
	while (temp != NULL)
	{
		old = temp;
		temp = temp->next;
		free(old);
		old = NULL;
	}
}

void	delete_first(t_lst **li)
{
	t_cmd	*temp;	
	t_cmd	*new;	

	new = NULL;
	temp = NULL;
	if (!(*li)->head)
		return ;
	temp = (*li)->head;
	if (temp != NULL)
	{
		new = temp->next;
		if (new)
			new->prev = NULL;
		if (temp->redir)
			delete_redir(temp->redir);
		free(temp->av);
		temp->av = NULL;
		temp->cmd = NULL;
		free((*li)->head);
		(*li)->head = new;
	}
}
