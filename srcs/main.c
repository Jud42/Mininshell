/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/19 15:04:44 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ms	g_ms;

void	msg_error(char *s1, char c, char *s2)
{
	ft_putstr_fd(s1, 2);
	if (c)
		write(2, &c, 1);
	if (s2)
		ft_putstr_fd(s2, 2);
}

int	exception_built(t_lst *li)
{
	if (!li->head)
		return (0);
	if (!ft_strncmp(li->head->cmd, "cd", 3) || \
	!ft_strncmp(li->head->cmd, "export", 7) || \
	!ft_strncmp(li->head->cmd, "unset", 6) || \
	!ft_strncmp(li->head->cmd, "exit", 5))
		return (1);
	return (0);
}

static int     get_line(t_lst *term)
{
        struct termios  news;

        tcgetattr(0, &term->saved);
        tcgetattr(0, &news);
        news.c_lflag &= ~ECHOCTL;
        tcsetattr(0, TCSAFLUSH, &news);
        init_signal();
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

int	main(int ac, char **av, char **envp)
{
	t_lst	li;

	g_ms.exit = 0;
	li.env = NULL;
	update_env(envp, &li);
	while (1)
	{
		if (!get_line(&li))
			break ;
		if (!error_exist(li.line))
		{
			init_shell(&li, lex_split(li.line, ' '));
			if (exception_built(&li) && !li.pipe)
				exec_builtin(li.head, &li);
			else
				exec_process(&li);
			clean_all(&li);
		}
		tcsetattr(0, TCSANOW, &li.saved);
		free(li.line);
	}
	free_env(&li.env);
	return (0);
}
