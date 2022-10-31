/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:04:24 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/17 19:58:24 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_d_push(t_redir *red, int len, int *fd)
{	
	char	*tmp;
	t_redir *red_temp;
	t_redir *node_free;

	tmp = ft_itoa(len);
	ft_putstr_fd("minishell: warning: here-document received EOF", 2);
	msg_error(" before delimiter => ", 0, red->name);
	write(1, "\n", 1);
	red_temp = red;
	while (red_temp)
	{
		node_free = red_temp;
		red_temp = red_temp->next;
		free(node_free);
	}
	free(tmp);
	close(*fd);
	//unlink(".heredoc");
	exit(1);
}

static void	zero_newline(char **old)
{
	char	*s;
	int		i;

	if (*old[0] == '\n')
		return ;
	s = ft_strdup(*old);
	free(*old);
	i = -1;
	while (s[++i] && s[i] != '\n')
		;
	s[i] = '\0';
	*old = s;
}

static int	process_heredoc(t_redir *red, int *file_temp)
{
	char		*temp;
	static int	len = 1;
	char		buf[sizeof(char)];

	temp = readline("> ");
	if (!temp)
		ctrl_d_push(red, len, file_temp);
	add_history(temp);
	zero_newline(&temp);
	if (ft_strcmp(red->name, temp) != 0)
	{
		++len;
		write(*file_temp, temp, ft_strlen(temp));
		write(*file_temp, "\n", 1);
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

void	here_doc(t_redir *red)
{
	int		file_temp;
	struct termios	news;
	struct termios	sav;

	tcgetattr(0, &news);
	sav = news;
	news.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &news);
	file_temp = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file_temp < 0)
	{
		msg_error("minishel: error: heredoc_ open()", '\n', NULL);
		exit(EXIT_FAILURE);
	}
	while (process_heredoc(red, &file_temp))
		;
	tcsetattr(0, TCSANOW, &sav);
	close(file_temp);
	exit(0);
}
