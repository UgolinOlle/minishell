/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 10:44:48 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:08:53 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin_exec.h"
#include "utils_exec.h"

static int	is_nflag(char *str);

int	exec_echo(char **cmd_array)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	while (cmd_array[++i])
	{
		if (cmd_array[i][0] == '\0')
			continue ;
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
	return (0);
}

static int	is_nflag(char *str)
{
	int	i;

	i = 0;
	skip_whitespace(str, &i);
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	skip_whitespace(str, &i);
	if (str[i])
		return (0);
	return (1);
}
