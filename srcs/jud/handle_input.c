/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:01:02 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/19 12:46:43 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_quote(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	while (s[++(*i)] && s[*i] != quote)
		;
	if (s[*i] == '\0')
	{
		msg_error("minishell: Error quote not close\n", 0, NULL);
		return (TRUE);
	}
	return (FALSE);
}

static int	help_error_redir(char *s, char c, int i, int redir)
{
	char	error;

	error = 0;
	if (redir > 2 || (redir == 2 && c == '|'))
		error = s[i];
	if (redirection(s[i + 1]) && s[i + 1] != s[i] && c != '|')
		error = s[i + 1];
	else if (s[i + 1] == ' ')
	{
		while (s[++i] && s[i] == ' ')
			;
		if (redirection(s[i]) && c != '|')
			error = s[i];
	}
	if (error)
	{
		msg_error("minishel: syntax error near unexpected token `" \
		, error, "\n");
		return (TRUE);
	}
	return (0);
}

static int	error_redirection(char *s, int *i)
{
	char	c;
	int		redir;

	redir = 0;
	c = s[*i];
	while (s[*i] && s[*i] == c)
	{
		++redir;
		if (help_error_redir(s, c, *i, redir))
			return (TRUE);
		++(*i);
	}
	--(*i);
	return (FALSE);
}

static int	help_error_exist(char *s)
{
	if (redirection(s[ft_strlen(s) - 1]) && s[ft_strlen(s) - 2] != '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected \
		token `newline'\n", 2);
		return (TRUE);
	}
	return (0);
}

int	error_exist(char *s)
{	
	int		i;

	if (help_error_exist(s))
		return (TRUE);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (error_quote(s, &i))
				return (TRUE);
		}
		else if (redirection(s[i]))
		{
			if (error_redirection(s, &i))
				return (TRUE);
		}
		else if (s[i] == ';' || s[i] == '\\')
		{
			msg_error("minishell: Error caracter forbiden\n", \
			0, NULL);
			return (TRUE);
		}
	}
	return (FALSE);
}
