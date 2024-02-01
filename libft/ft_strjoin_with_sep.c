/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_sep.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:15:38 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 00:16:24 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_with_sep(char const *s1, char const *s2, char sep)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s2[i] != ' ' && s2[i] != '\0')
		i++;
	len = ft_strlen(s1) + i + 1;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	result[i] = sep;
	while (s2[j] != ' ' && s2[j] != '\0')
		result[++i] = s2[j++];
	result[++i] = '\0';
	return (result);
}
