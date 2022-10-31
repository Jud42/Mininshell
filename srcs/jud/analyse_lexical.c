/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_lexical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:11:10 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 16:56:05 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	home_sign(char **s, t_lst *li)
{
	char	*path_home;
	char	*temp_str;
	char	*temp;

	if ((*s)[0] == '~' && ((*s)[1] == '/' || !(*s)[1]))
	{
		temp_str = *s;
		path_home = get_env_value("HOME", li);
		temp = ft_strjoin(path_home, ++(temp_str));
		free(*s);
		*s = temp;
		temp = NULL;
	}
}

static void    write_env(char **s, char *env_value)
{
        int     i;
        if (!env_value)
                return ;
        i = -1;
        while (env_value[++i])
                *(*s)++ = env_value[i];
        free(env_value);
}

static void    update_word(char *s, char *temp, t_lst *li)
{
        int     i;

        i = -1;
        while (s[++i])
        {
                if (s[i] == '\'')
                        while (s[++i] != '\'' && s[i])
                                *temp++ = s[i];
                else if (s[i] == '\"')
                {
                        while (s[++i] != '\"' && s[i])
                        {
                                if (s[i] == '$' && s[i + 1] != ' ')
                                        write_env(&temp, handle_sign(s, &i, li));
                                else 
                                        *temp++ = s[i];
                        }
                }
                else if (s[i] == '$' && s[i + 1])
                        write_env(&temp, handle_sign(s, &i, li));
                else
                        *temp++ = s[i];
        }
        *temp = '\0';
        free(s);
}

void	handle_action(t_lst **li)
{
	int		i;
	int		j;
	int		flag;
	char	*temp;

	i = -1;
	while ((*li)->tab[++i])
	{
		home_sign(&(*li)->tab[i], *li);
		j = -1;
		if (quote_exist((*li)->tab[i]))
		{
			temp = malloc(sizeof(char) * \
			len_new_word((*li)->tab[i], *li) + 1);
			if (!temp)
				return ;
			update_word((*li)->tab[i], temp, *li);
			(*li)->tab[i] = temp;
		}
	}
}
