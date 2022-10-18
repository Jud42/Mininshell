/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_treat_quote_dollar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:16:34 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/19 17:27:35 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	recheck_cmp(char *env, char *temp)
{
	int	i;

	i = -1;
	while (env[++i] && env[i] != '=')
		;
	if (ft_strncmp(env, temp, i) == 0)
		return (TRUE);
	else
		return (FALSE);
}

char	*take_val_var(char *s)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (s[++i] && s[i] != '=')
		;
	++i;
	j = i;
	while (s[i])
		i++;
	temp = malloc(sizeof(char) * (i - j + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (s[j])
		temp[++i] = s[j++];
	temp[++i] = '\0';
	return (temp);
}
