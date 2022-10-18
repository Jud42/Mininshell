/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:03:26 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/19 17:32:35 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **cmd)
{
	bool	flag;
	int		i;

	i = 1;
	flag = false;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		flag = true;
		i = 2;
	}
	while (cmd && cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (flag == false)
		printf("\n");
	g_ms.exit = 0;
}
