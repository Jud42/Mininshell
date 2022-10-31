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
/*--------------------------------*/

int	len_dollar(char *s, int *i, t_lst *li)
{
	int	ret;
	char	*temp;

	ret = 0;
	temp = handle_sign(s, i, li);
	if (temp)
	{
		ret = ft_strlen(temp);
		free(temp);
	}
	return (ret);
}
/*------------------------------------------*/

int	len_d_quote(char *s, t_lst *li, int *i)
{
	int		car;
	char	*temp;

	car = 0;
	temp = NULL;
	while (s[++(*i)] != '\"' && s[*i])
	{
		if (s[*i] == '$' && (s[(*i) + 1] != ' ' && \
		s[(*i) + 1] != '\"' && s[(*i) + 1]))
		{
			temp = handle_sign(s, i, li);
			if (temp) 
			{
				car += ft_strlen(temp);
				free(temp);
			}
		}
		else
			car++;
	}
	return (car);
}
/*--------------------------------------*/

int	len_new_word(char *s, t_lst *li)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
			while (s[++i] != '\'' && s[i])
				++ret;
		else if (s[i] == '\"')
			ret += len_d_quote(s, li, &i);
		else if (s[i] == '$' && s[i + 1])
			ret += len_dollar(s, &i, li);
		else
			ret++;
	}
	return (ret);
}

/*---------------------------------*/
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
	--(*i);
	return (ret);
}
