/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:27:43 by rmamison          #+#    #+#             */
/*   Updated: 2022/05/24 20:57:06 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include "./ft_printf/include/ft_printf.h"
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_type{
	char	data;
	int		fd;
	int		max;
	int		pos;
}	t_type;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t d);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *str, const char *substr, size_t len);

#endif
