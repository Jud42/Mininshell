/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:10:00 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/17 20:09:45 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_print(char *token, int exit)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", \
		STDERR_FILENO);
	ft_putendl_fd(token, STDERR_FILENO);
	g_ms.exit = exit;
	return (TRUE);
}

void	ft_error(char *func, char *str)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(func, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putchar_fd('`', STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
}
