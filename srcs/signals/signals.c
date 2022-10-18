/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:54:12 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/19 12:49:51 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rl_replace_line(const char *text, int clear_undo);

void	child_signal(int flag)
{	
	signal(SIGINT, SIG_DFL);
	if (flag == HEREDOC)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, SIG_DFL);
}

void	sig_handler(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ms.exit = 1;
}

void	init_signals(void)
{
	if (g_ms.pid_sig)
		signal(SIGINT, SIG_IGN);
	else
		signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	get_line(t_lst *term)
{
	struct termios	news;

	tcgetattr(0, &term->saved);
	tcgetattr(0, &news);
	news.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSAFLUSH, &news);
	init_signals();
	term->line = readline(BOLDGREEN"minishell$> "RESET);
	if (!term->line)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (*term->line)
		add_history(term->line);
	return (1);
}
