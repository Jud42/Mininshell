/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quote_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:20:34 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 17:27:41 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	len_var(char *s, int i)
{
	int	ret;

	ret = 0;
	while ((s[++i]) && ((int) s[i] > 47))
		ret++;
	return (ret);
}
/*------------------------------------------*/

static void	help_len_d_quote(char **temp, int *dollar)
{
	if (*temp)
	{	
		*dollar += (int)ft_strlen(*temp);
		free(*temp);
	}
}

int	len_d_quote(char *s, t_lst *li)
{
	int		i;
	int		dollar;
	int		car;
	char	*temp;

	i = 0;
	dollar = 0;
	car = 0;
	temp = NULL;
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] != ' ' && s[i + 1]))
		{
			temp = handle_sign(s, &i, li);
			help_len_d_quote(&temp, &dollar);
		}
		else if (s[i] != '\"')
			car++;
		if (s[i] != '$' || s[i] == '$' && (s[i + 1] == ' ' || !s[i + 1]))
			i++;
	}
	return (car + dollar);
}
/*--------------------------------------*/

char	*handle_sign(char *s, int *i, t_lst *li)
{
	char	*temp;
	char	*ret;
	int		j;

	temp = malloc(sizeof(char) * (len_var(s, *i) + 1));
	if (!temp)
		return (NULL);
	j = -1;
	while ((s[++(*i)]) && ((int)s[*(i)] > 47))
		temp[++j] = s[(*i)];
	temp[++j] = '\0';
	if (!temp[1] && temp[0] == '?')
		ret = ft_itoa(g_ms.exit);
	else
		ret = ft_strdup(get_env_value(temp, li));
	free(temp);
	return (ret);
}
