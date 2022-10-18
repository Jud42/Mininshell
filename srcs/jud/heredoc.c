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

static void	ctrl_d_push(char *limiter, int len)
{	
	char	*tmp;

	tmp = ft_itoa(len);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	msg_error(tmp, 0, " delimited by end-of-file ");
	msg_error("(wanted `", 0, limiter);
	write(2, "')\n", 3);
	free(tmp);
	exit(0);
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
		ctrl_d_push(red->name, len);
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

int	here_doc(t_redir *red)
{
	int				file_temp;
	struct termios	news;
	struct termios	sav;

	tcgetattr(0, &news);
	sav = news;
	news.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &news);
	file_temp = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file_temp < 0)
	{
		msg_error("minishel: error: open()", '\n', NULL);
		exit(EXIT_FAILURE);
	}
	if (file_temp < 0)
		msg_error("Error: file_temp_here_doc\n", 0, NULL);
	while (process_heredoc(red, &file_temp))
		;
	tcsetattr(0, TCSANOW, &sav);
	close(file_temp);
	return (1);
}
