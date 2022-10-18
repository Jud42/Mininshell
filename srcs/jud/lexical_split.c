/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:30:03 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 11:36:30 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_word(char *s, char sep, int i)
{
	int		ret;
	char	quote;

	quote = ' ';
	ret = 0;
	if (redirection(s[i]) == 1)
		return (count_redirection(s, i));
	while (s[i] && (s[i] != sep && !redirection(s[i])))
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			ret++;
			while (s[++i] && s[i] != quote)
				ret++;
		}
		ret++;
		i++;
	}
	return (ret);
}
/*---------------------------------------------------*/

static void	help_take_word(char *s, char **word, char sep, int *i)
{
	char	quote;
	int		j;

	j = -1;
	quote = 0;
	while (s[*i] && (s[*i] != sep && !redirection(s[*i])))
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{	
			quote = s[*i];
			(*word)[++j] = s[*i];
			while (s[++(*i)] && s[*i] != quote)
				(*word)[++j] = s[*i];
		}
		(*word)[++j] = s[(*i)];
		++(*i);
	}
	(*word)[++j] = '\0';
}

static char	*take_word(char *s, char sep, int *i)
{
	char	*word;
	char	quote;

	word = malloc(sizeof(char) * (len_word(s, sep, *i) + 1));
	if (!word)
		return (NULL);
	if (redirection(s[*i]) == 1)
		write_redirection(&word, s, i);
	else
		help_take_word(s, &word, sep, i);
	--(*i);
	return (word);
}
/*-------------------------------------------------*/

char	**lex_split(char *s, char sep)
{
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	j = -1;
	i = -1;
	tab = (char **)malloc(sizeof(char *) * (count_sep(s, sep) + 1));
	if (!tab)
		return (NULL);
	while (++i <= (ft_strlen(s)))
	{	
		if (!s[i])
			break ;
		if (s[i] == sep)
			while (s[++i] == sep)
				;
		if (s[i] != sep && s[i])
			tab[++j] = take_word(s, sep, &i);
	}
	tab[j + 1] = NULL;
	j = -1;
	return (tab);
}
