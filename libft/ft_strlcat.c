/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:58:30 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:10:50 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dst && dst[i])
		i++;
	j = -1;
	while (src && src[++j])
		dst[i + j] = src[j];
	dst[i + j] = '\0';
}
