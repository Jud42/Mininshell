/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:10:49 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 16:41:01 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	help_std_in_out(t_cmd *cmd, t_redir *redir)
{
	if (cmd->infile < 0 || cmd->outfile < 0)
	{
		if (redir->sign == REDIR_IN)
		{
			msg_error("minishell: ", 0, redir->name);
			write(2, ": No such file or directory\n", 28);
			//exit(EXIT_FAILURE);
		}
		else
			msg_error("Error: outfile", 0, "\n");
		return (1);
	}
	redir->pos = 0;
	return (0);
}

static int	std_in_out(t_cmd *cmd, t_redir *redir)
{
	if (redir->sign == HEREDOC)
	{
		cmd->infile = open(".heredoc", O_RDONLY);
		if (cmd->infile < 0)
		{
			msg_error("minishel: error: open() .heredoc\n", 0, NULL);
			return (1);
		}
	}
	else if (redir->sign == REDIR_IN)
		cmd->infile = open(redir->name, O_RDONLY);
	else if (redir->sign == REDIR_OUT_S)
		cmd->outfile = open(redir->name, \
		O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (redir->sign == REDIR_OUT_D)
		cmd->outfile = open(redir->name, \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (help_std_in_out(cmd, redir))
		return (1);
	return (0);
}

static int	process_daddy_heredoc(pid_t pid)
{
	int	status;
	
	g_ms.pid_child = pid;
	init_signal();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			g_ms.exit = 128 + status;
		}
	}
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) == 1)
			g_ms.exit = 0;
	g_ms.pid_child = 0;
	return (status);
}

static int	fork_heredoc(t_redir **red, int flag)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		init_child_signal(HEREDOC);
		here_doc(*red);
	}
	return(process_daddy_heredoc(pid));
}

int	init_redir(t_cmd *node, t_lst *li)
{
	t_cmd	*temp_node;
	t_redir	*red;

	temp_node = node;
	while (temp_node)
	{
		red = temp_node->redir;
		while (red)
		{
			if (red->sign == HEREDOC)
				if (fork_heredoc(&red, red->sign))
					return (1);
			if (std_in_out(temp_node, red))
				return (1);
			red = red->next;
		}
		temp_node = temp_node->next;
	}
	return (0);
}
