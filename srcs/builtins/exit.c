/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:10:06 by artclave          #+#    #+#             */
/*   Updated: 2024/02/08 01:34:31 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	get_new_exit_num(char *cmd, int new_line);
static void	check_numeric_argument(char *str, int new_line, __int128_t num);
__int128_t	atoi_128bits(const char *str);

void	exec_exit(char **cmd_array, t_redir *redir)
{
	int	new_exit_num;
	int	new_line;

	new_line = FALSE;
	if (!redir || redir->type != PIPE)
	{
		ft_putstr_fd("exit", 1);
		new_line = TRUE;
	}
	if (cmd_array[1] == NULL)
		exit(0);
	new_exit_num = get_new_exit_num(cmd_array[1], new_line);
	if ((cmd_array[2]))
	{
		if (new_line == TRUE)
			ft_putstr_fd("\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		exit(1);
	}
	exit(new_exit_num);
}

__int128_t	atoi_128bits(const char *str)
{
	int			i;
	int			sign;
	__int128_t	num;

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
		num *= 10;
		num += (str[i++] - '0');
	}
	return (num * sign);
}

static int	get_new_exit_num(char *cmd, int new_line)
{
	__int128_t	num;
	int			i;

	i = 0;
	skip_whitespace(cmd, &i);
	num = atoi_128bits(cmd);
	check_numeric_argument(&cmd[i], new_line, num);
	if (num > 255 || num < 0)
		return ((int)(num % 256));
	return ((int)num);
}

static void	check_numeric_argument(char *str, int new_line, __int128_t num)
{
	int	i;

	i = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i])
	{
		if (num > LLONG_MAX || num < LLONG_MIN || (str[i]) == FALSE)
		{
			if (new_line == TRUE)
				ft_putstr_fd("\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required", 2);
			exit(255);
		}
	}
}
