/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:00 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/17 20:04:18 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, PATH_MAX);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	pwd = NULL;
	g_ms.exit = 0;
	return ;
}
