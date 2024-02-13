/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:38:06 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:09:32 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin_exec.h"
#include "utils_exec.h"

static int			get_new_exit_num(char *cmd);
static int			check_numeric_argument(char *str, __int128_t num);
static __int128_t	atoi_128bits(const char *str);

int	exec_exit(char **cmd_array, t_cmd *cmd)
{
	int		new_exit_num;
	t_redir	*redir;

	redir = cmd->redir;
	if (!redir || redir->type != PIPE)
		ft_putstr_fd("exit\n", 1);
	if (cmd_array[1] == NULL)
		exit(0);
	new_exit_num = get_new_exit_num(cmd_array[1]);
	if (new_exit_num == -1)
		return (255);
	if ((cmd_array[2]))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (new_exit_num);
}

static int	get_new_exit_num(char *cmd)
{
	__int128_t	num;
	int			i;

	i = 0;
	skip_whitespace(cmd, &i);
	num = atoi_128bits(cmd);
	if (check_numeric_argument(&cmd[i], num) == 255)
		return (-1);
	if (num > 255 || num < 0)
		return ((int)(num % 256));
	return ((int)num);
}

static __int128_t	atoi_128bits(const char *str)
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

static int	check_numeric_argument(char *str, __int128_t num)
{
	int	i;

	i = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i])
	{
		if (num > LLONG_MAX || num < LLONG_MIN
			|| str_is_numerical(&str[i]) == FALSE)
		{
			print_error("exit: ", str, ": numeric argument required");
			return (255);
		}
	}
	return (0);
}
