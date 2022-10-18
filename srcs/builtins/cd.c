/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:33:24 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/19 14:49:19 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_only(t_lst *ms)
{
	char	*path;

	path = get_env_value("HOME", ms);
	if (path == NULL)
	{
		g_ms.exit = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (path);
}

void	print_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putchar_fd('\n', 2);
}

int	ft_cd(char *path, t_lst *ms)
{
	char	tmp[PATH_MAX];
	char	*temp_join;
	char	*nwd;

	getcwd(tmp, PATH_MAX);
	if (!path)
		nwd = cd_only(ms);
	else
		nwd = path;
	if (chdir(nwd) != 0)
	{
		g_ms.exit = 1;
		msg_error("minishell: cd:", ' ', nwd);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	temp_join = ft_strjoin("OLDPWD=", tmp);
	ft_export(temp_join, ms);
	free(temp_join);
	temp_join = ft_strjoin("PWD=", getcwd(tmp, PATH_MAX));
	ft_export(temp_join, ms);
	free(temp_join);
	return (0);
}
