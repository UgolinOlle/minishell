/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:44:10 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 14:42:54 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <gmp.h>

int		ft_strlen(const char *s);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *src);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);

void	ft_strcat(char *dst, char *src);
char	*ft_strjoin_with_sep(char const *s1, char const *s2, char sep);

#endif
