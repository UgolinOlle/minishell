/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:50:56 by artclave          #+#    #+#             */
/*   Updated: 2024/02/08 02:06:50 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	x;

	x = (char)c;
	while (*s != '\0')
	{
		if (*s == x)
			return ((char *) s);
		s++;
	}
	if (x == '\0')
		return ((char *)s);
	return ((void *)0);
}
