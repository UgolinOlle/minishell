/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_numerical.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:08:45 by artclave          #+#    #+#             */
/*   Updated: 2024/02/07 05:01:24 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	str_is_numerical(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_digit(str[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
