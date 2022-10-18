/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:03 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/17 20:03:30 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	ft_str_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	if (ft_atoi(str) >= 256)
		exit(ft_atoi(str) - 256);
	return (1);
}

void	ft_exit(char **cmd, t_lst *li)
{
	int	status;

	status = 0;
	write(1, "exit\n", 6);
	if (cmd[1] != NULL && ft_str_isdigit(cmd[1]) == 0)
	{
		status = 255;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else if (cmd[1] != NULL && cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_ms.exit = 127;
		if (li->pipe)
			exit(g_ms.exit);
		return ;
	}
	else if (cmd[1] != NULL && ft_str_isdigit(cmd[1]) == 1)
		status = ft_atoi(cmd[1]);
	free_all(li);
	exit(status);
}
