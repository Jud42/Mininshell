/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quote_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:20:34 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 17:27:29 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*news_s_quote(char *s)
{	
	int		i;
	int		j;
	int		quote;
	char	*temp;

	i = -1;
	quote = 0;
	while (s[++i])
		if (s[i] == '\'')
			quote++;
	temp = malloc(sizeof(char) * ((i - quote) + 1));
	if (!temp)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != '\'')
			temp[j++] = s[i];
	temp[j] = '\0';
	return (temp);
}

/*--------------*/
static void	help_news_d_quote(char **env_val, char **temp, int *j)
{
	int	a;

	a = 0;
	if (*env_val)
	{
		a = -1;
		while ((*env_val)[++a])
			(*temp)[(*j)++] = (*env_val)[a];
		free(*env_val);
	}
}

char	*news_d_quote(char *s, t_lst *li)
{
	int		i;
	int		j;
	int		a;
	char	*temp;
	char	*env_val;

	temp = malloc(sizeof(char) * (len_d_quote(s, li) + 1));
	if (!temp)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '$' && (s[i + 1] != ' ' && s[i + 1] != '\"'\
			&& s[i + 1] != '\'' && s[i + 1]))
		{
			env_val = handle_sign(s, &i, li);
			help_news_d_quote(&env_val, &temp, &j);
			--i;
		}
		else if (s[i] && s[i] != '\"')
			temp[j++] = s[i];
	}
	temp[j] = '\0';
	return (temp);
}
