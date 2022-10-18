/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:05:13 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 12:45:59 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_pid(t_lst **li)
{
	(*li)->pid = malloc(sizeof(pid_t) * ((*li)->pipe + 1));
	if (!(*li)->pid)
	{
		msg_error("Error: malloc(): pid: ", 0, NULL);
		exit(EXIT_FAILURE);
	}
}

void	init_pipe(t_lst *li)
{
	int	i;

	li->tube_fd = (int **)malloc(sizeof(int *) * li->pipe);
	if (!li->tube_fd)
	{
		msg_error("error: allocaion tube_fd\n", 0, NULL);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < li->pipe)
	{
		li->tube_fd[i] = malloc(sizeof(int) * 2);
		if (!li->tube_fd)
		{
			msg_error("error: allocation *tube_fd\n", 0, NULL);
			exit(EXIT_FAILURE);
		}
		if (pipe(li->tube_fd[i]) == -1)
		{
			free_pipe(li);
			msg_error("Error: function pipe\n", 0, NULL);
		}
	}
}

int	check_pipe(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (tab[++j])
		if (ft_strcmp(tab[j], "|") == 0)
	i++;
	return (i);
}

int	check_redir(t_lst **li)
{
	int		i;
	int		ret;
	char	**tab_temp;

	ret = 0;
	i = -1;
	(*li)->heredoc = 0;
	tab_temp = (*li)->tab;
	while (tab_temp[++i])
	{
		if (!ft_strncmp(tab_temp[i], "<<", 3))
		{
			(*li)->heredoc++;
			ret = TRUE;
		}
		if (!ft_strncmp(tab_temp[i], "<", 2) || \
		!ft_strncmp(tab_temp[i], ">", 2) || \
		!ft_strncmp(tab_temp[i], ">>", 3))
			ret = TRUE;
	}
	return (ret);
}

void	init_shell(t_lst *li, char **tab)
{
	int	i;

	li->tab = tab;
	tab = NULL;
	li->nb_arg = 0;
	i = -1;
	while (li->tab[++i])
		li->nb_arg++;
	li->pipe = check_pipe(li->tab);
	li->redirection = check_redir(&li);
	li->head = NULL;
	li->pid = NULL;
	handle_action(&li);
	create_list(&li);
}
