/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:55:29 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 16:40:52 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	help_ft_exec(char **cmd, char **tab, t_lst *li)
{
	int	i;

	i = -1;
	take_path(&tab, *cmd, li);
	if (!tab)
	{
		msg_error("minishell: ", 0, *cmd);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	while (tab[++i] && access(tab[i], X_OK) != 0)
		;
	if (!tab[i])
	{
		free_tab(tab);
		return (0);
	}
	*cmd = ft_strdup(tab[i]);
	free_tab(tab);
	return (1);
}

static int	ft_exec(t_cmd *node, t_lst *li, pid_t *pid)
{
	char		**tab;

	tab = NULL;
	if (!ft_strchr(node->cmd, '/'))
		if (!help_ft_exec(&node->cmd, tab, li))
			return (0);
	tab = env_2_str(li);
	if (execve(node->cmd, node->av, tab) == -1)
	{
		if (ft_strchr(node->cmd, '/'))
			check_error(node->cmd);
		free_tab(tab);
		return (0);
	}
	free_tab(tab);
	return (1);
}

static void	process_daddy(t_lst **li, pid_t *pid)
{
	int	status;
	int	i;

	i = -1;
	close_fd(NULL, li);
	while (++i <= (*li)->pipe)
	{
		g_ms.pid_child = pid[i];
		init_signal();
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit: 3\n", 8);
			else if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			g_ms.exit = 128 + status;
		}
		if (WIFEXITED(status))
			g_ms.exit = WEXITSTATUS(status);
		g_ms.pid_child = 0;
	}
}

static int	process_child(t_lst *li, t_cmd node, int x, pid_t *pid)
{
	init_child_signal(0);
	if (node.infile)
		dup_fd(node.infile, STDIN_FILENO);
	if (node.outfile)
		dup_fd(node.outfile, 1);
	if (x == 0 && li->pipe && !node.outfile)
		dup_fd(li->tube_fd[x][1], 1);
	if (x > 0)
	{
		if (!node.infile)
			dup_fd(li->tube_fd[x - 1][0], 0);
		if (x != li->pipe && !node.outfile)
			dup_fd(li->tube_fd[x][1], 1);
	}
	close_fd(&node, &li);
	if (check_builtin(node.cmd) == TRUE)
		exec_builtin(&node, li);
	else if (node.cmd && !ft_exec(&node, li, &pid[x]))
	{
		msg_error("minishell: ", 0, node.av[0]);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	exit(0);
}

void	exec_process(t_lst *li)
{
	int		status;	
	int		x;

	if (li->redirection)
		if (init_redir(li->head, li))
			return ;
	malloc_pid(&li);
	if (li->pipe)
		init_pipe(li);
	x = -1;
	while (++x <= li->pipe)
	{
		li->pid[x] = fork();
		if (li->pid[x] == -1)
			exit(EXIT_FAILURE);
		else if (li->pid[x] == 0)
			process_child(li, *li->head, x, li->pid);
		delete_first(&li);
	}
	process_daddy(&li, li->pid);
}
