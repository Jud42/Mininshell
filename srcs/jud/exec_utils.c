/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:54:21 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 16:40:50 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	help_check(char *path, char *t, int i)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (sb.st_mode & S_IFDIR)
		ft_putstr_fd(": Is a directory\n", 2);
	else if (sb.st_mode & S_IFREG)
	{
		if (i == 1)
		{
			ft_putstr_fd(": Not a directory\n", 2);
			free(t);
		}
		else
			ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (i == 1)
		free(t);
}

void	check_error(char *path)
{
	int			i;
	char		*t;

	i = 0;
	msg_error("minishell: ", 0, path);
	if (path[ft_strlen(path) - 1] == '/')
	{
		t = malloc(sizeof(char) * (ft_strlen(path) - 1));
		if (!t)
			return ;
		ft_strlcpy(t, path, ft_strlen(path));
		path = t;
		i = 1;
	}
	help_check(path, t, i);
	exit(127);
}

void	dup_fd(int fd_in, int fd_out)
{
	if (dup2(fd_in, fd_out) < 0)
	{
		msg_error("error: dup2\n", 0, NULL);
		exit(EXIT_FAILURE);
	}
}

void	close_fd(t_cmd *node, t_lst **li)
{
	int	i;

	i = -1;
	if (!(*li)->pipe)
		return ;
	while (++i < (*li)->pipe)
	{
		close((*li)->tube_fd[i][0]);
		close((*li)->tube_fd[i][1]);
	}
	if (node)
	{
		if (node->infile)
			close(node->infile);
		if (node->outfile)
			close(node->outfile);
	}
}

void	take_path(char	***dest, char *cmd, t_lst *li)
{
	char	*tmp_a;
	char	*tmp_b;
	int		i;	

	*dest = ft_split(get_env_value("PATH", li), ':');
	if (!*dest)
		return ;
	i = -1;
	while ((*dest)[++i])
	{
		tmp_a = ft_strjoin((*dest)[i], "/");
		free((*dest)[i]);
		tmp_b = ft_strjoin(tmp_a, cmd);
		free(tmp_a);
		(*dest)[i] = tmp_b;
	}
}
