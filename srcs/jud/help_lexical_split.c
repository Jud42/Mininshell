/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:30:03 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 10:56:14 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exception(char *s, int *i, int flag)
{
	char	c;

	c = s[*i];
	if (flag == QUOTE)
		while (s[++(*i)] && s[*i] != c)
			;
	else if (flag == REDIR)
		while (s[++(*i)] && s[*i] == c)
			;
}

static void	help_count_sep(char *s, int *i, int *ret, int *time)
{
	if (redirection(s[*i]))
	{
		exception(s, i, REDIR);
		(*ret)++;
		--(*i);
	}
	if (*time == 1)
		(*ret)++;
	*time = 0;
}

int	count_sep(char *s, char sep)
{
	int	ret;
	int	time;
	int	i;

	time = 0;
	ret = 0;
	i = -1;
	while (s[++i])
	{
		while (s[i] && (s[i] != sep && !redirection(s[i])))
		{
			if (s[i] == '\'' || s[i] == '\"')
				exception(s, &i, QUOTE);
			++i;
			time = 1;
		}
		help_count_sep(s, &i, &ret, &time);
	}
	return (ret);
}
