/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:00:18 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 12:55:18 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*temp;
	t_env	*node;

	temp = *env;
	if (!temp)
		return ;
	while (temp->next)
	{
		node = temp;
		temp = temp->next;
		free(node->value);
		free(node);
	}
	free(temp->value);
	free(temp);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

void	free_list(t_lst *li)
{
	if (li->head)
		return ;
	while (li->head)
		delete_first(&li);
}

void	free_pipe(t_lst *li)
{
	int	i;

	if (!li->pipe)
		return ;
	i = -1;
	while (++i < li->pipe)
		free(li->tube_fd[i]);
	free(li->tube_fd);
	li->tube_fd = NULL;
}

void	free_all(t_lst *li)
{
	int	i;

	i = -1;
	if (li->tab)
		free_tab(li->tab);
	li->tab = NULL;
	if (li->pipe)
		free_pipe(li);
	if (li->pid)
		free(li->pid);
	li->pid = NULL;
	free_list(li);
}
