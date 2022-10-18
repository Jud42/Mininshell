/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:56:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/17 16:44:29 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_env(char *str, t_lst *ms)
{
	t_env	*newenv;
	t_env	*temp;

	newenv = malloc(sizeof(t_env));
	if (!newenv)
		exit (127);
	newenv->value = ft_strdup(str);
	newenv->next = NULL;
	if (ms->env)
	{
		temp = ms->env;
		while (temp->next)
			temp = temp->next;
		temp->next = newenv;
	}
	else
		ms->env = newenv;
	ms->n_env++;
	return ;
}

int	update_env(char **env, t_lst *ms)
{
	int		i;

	if (env == NULL)
		return (1);
	ms->n_env = 0;
	i = -1;
	while (env[++i] != NULL)
		new_env(env[i], ms);
	return (0);
}

char	**env_2_str(t_lst *ms)
{
	int		i;
	char	**str;
	t_env	*env;

	env = ms->env;
	str = malloc(sizeof(char *) * ms->n_env);
	if (!str)
		return (NULL);
	i = -1;
	while (env)
	{
		str[++i] = ft_strdup(env->value);
		env = env->next;
	}
	str[++i] = NULL;
	return (str);
}

char	*get_env_value(char *env, t_lst *ms)
{
	t_env	*tmp;
	char	*val;
	int		length;

	length = ft_strlen(env);
	tmp = ms->env;
	val = NULL;
	while (tmp->value)
	{
		if (ft_strcmp(tmp->value, env) == 61)
			val = ft_strnstr(tmp->value, env, length);
		if (val)
		{
			val += 1 + length;
			return (val);
		}
		if (!tmp->next)
			break ;
		else
			tmp = tmp->next;
	}
	return (NULL);
}
