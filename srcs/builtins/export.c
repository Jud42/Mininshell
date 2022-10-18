/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/17 20:03:47 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sort_export(t_lst *ms)
{
	char	**export;
	char	*tmp;
	int		i;
	int		j;

	export = env_2_str(ms);
	i = -1;
	while (export[++i])
	{
		j = i;
		while (export[++j])
		{
			if (ft_strcmp(export[i], export[j]) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
		}
	}
	i = -1;
	while (export[++i])
		printf("declare -x %s\n", export[i]);
	free_2ptr(export);
}

static void	sort_env(char *str, t_env **env)
{
	t_env	*cur;
	t_env	*aft;
	t_env	*tmp;

	tmp = *env;
	while (tmp->next)
	{
		aft = tmp;
		tmp = tmp->next;
	}
	aft->next = NULL;
	cur = *env;
	while (cur->next)
	{
		aft = cur->next;
		if (!ft_strncmp(aft->value, "OLDPWD=", 7))
		{
			tmp->next = aft;
			cur->next = tmp;
			return ;
		}
		cur = cur->next;
	}
}

static int	check_export(char *str, t_lst *ms)
{
	t_env	*temp;
	char	**id;
	int		i;

	temp = ms->env;
	i = -1;
	while (str[++i] && str[i] != '=')
		;
	i++;
	while (temp)
	{
		if (!ft_strncmp(temp->value, str, i))
		{
			free(temp->value);
			temp->value = ft_strdup(str);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_export(char *str, t_lst *ms)
{
	int		check;
	int		i;

	if (*str == '$' || *str == '*' || ft_isdigit(*str) == 1)
	{
		ft_error("export", str);
		return (1);
	}
	if (!check_export(str, ms))
	{
		new_env(str, ms);
		sort_env(str, &ms->env);
	}
	return (0);
}
