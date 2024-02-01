/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:16:02 by artclave          #+#    #+#             */
/*   Updated: 2024/01/29 08:53:21 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_echo(char **cmd_array)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	//GET ENV EXPANDABLES $
	while (cmd_array[++i])
	{
		if (is_nflag(cmd_array[i]) && n_flag + 1 == i)
		{
			n_flag++;
			continue ;
		}
		write(STDOUT_FILENO, cmd_array[i], ft_strlen(cmd_array[i]));
		if (cmd_array[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	exit (0);
}

int	is_nflag(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);
	}
	return (1);
}
