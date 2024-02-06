/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:10:06 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 15:58:40 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	get_new_exit_num(char *cmd);

void	exec_exit(char **cmd_array, t_redir *redir, t_exec *ex)
{
	int	new_exit_num;

	if (!redir || redir->type != PIPE)
	{
		ft_putstr_fd("exit\n", 2);
		ex->quit_program = TRUE;
	}
	if (cmd_array[1] == NULL)
		exit(0);
	new_exit_num = get_new_exit_num(cmd_array[1]);
	if ((cmd_array[2]))
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit(1);
	}
	exit(new_exit_num);
}

static int	get_new_exit_num(char *cmd)
{
	int	num;
	int	digits;
	int	i;

	i = 0;
	digits = 0;
	skip_whitespace(cmd, &i);
	num = abs(ft_atoi(cmd));
	while (num > 0 && digits++ > -1)
		num /= 10;
	if (cmd[i] == '+' || cmd[i] == '-')
		digits++;
	if (digits < ft_strlen(&cmd[i]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : numeric argument required\n", 2);
		return (255);
	}
	num = ft_atoi(cmd);
	if (num > 255 || num < 0)
		return ((unsigned int)num & 0xFF);
	return (num);
}
