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

int     redir_exist(char *s)
{
        int     i;

        i = 0;
        if (s && *s == '<' || *s == '>')
        {
                if (s[i] == '<' && s[i + 1] == '<')
                        return (HEREDOC);
                else if (s[i] == '<')
                        return (REDIR_IN);
                else if (s[i] == '>' && s[i + 1] == '>')
                        return (REDIR_OUT_D);
                else if (s[i] == '>')
                        return (REDIR_OUT_S);
        }
        return (FALSE);
}

void	delete_redir(t_redir *node)
{
	t_redir	*temp;	
	t_redir	*old;	

	old = NULL;
	temp = NULL;
	if (!node)
		return ;
	temp = node;
	while (temp)
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
	new = temp->next;
	if (temp->redir)
		delete_redir(temp->redir);
	if (temp->av)
		free(temp->av);
	temp->av = NULL;
	temp->cmd = NULL;
	free((*li)->head);
	(*li)->head = new;
}
