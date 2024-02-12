/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:02:34 by artclave          #+#    #+#             */
/*   Updated: 2024/02/10 06:43:03 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_last_digit(char c, int sign)
{
	int	num;

	num = c + '0';
	if ((sign == -1 && num > 8) || (sign == 1 && num > 7))
		return (1);
	else
		return (0);
}

static int	ft_buffer_overflow(int sign)
{
	if (sign == -1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (num > INT_MAX || (num == INT_MAX && ft_last_digit(str[i], sign)))
			return (ft_buffer_overflow(sign));
		num *= 10;
		num += (str[i++] - '0');
	}
	return ((int)num * sign);
}
