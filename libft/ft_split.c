/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:12:30 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/17 20:04:53 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(const char *s, char c)
{
	int	i;
	int	j;
	int	def;

	i = 0;
	def = 0;
	j = -1;
	while (s[++j])
	{
		if (s[j] != c && def == 0)
		{
			def = 1;
			i++;
		}
		else if (s[j] == c)
			def = 0;
	}
	return (i);
}

static char	*word_dup(char const *s, int deb, int fin)
{
	char	*word;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	word = (char *) malloc (sizeof(char) * (fin - deb + 1));
	if (!word)
		return (NULL);
	while (deb < fin)
		word[i++] = s[deb++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		deb;
	int		fin;
	size_t	j;
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **) malloc (sizeof(char *) * (count(s, c) + 1));
	if (!tab)
		return (NULL);
	deb = -1;
	fin = -1;
	j = 0;
	while (fin <= (int)ft_strlen(s))
	{
		if (s[++fin] != c && deb < 0)
			deb = fin;
		else if ((s[fin] == c || fin == (int)ft_strlen(s)) && deb >= 0)
		{
			tab[j++] = word_dup (s, deb, fin);
			deb = -1;
		}
	}
	tab[j] = 0;
	return (tab);
}
