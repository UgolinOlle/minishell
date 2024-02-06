/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:10:06 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:29:30 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	get_new_exit_num(char *cmd);

void	exec_exit(char **cmd_array, t_redir *redir, t_exec *ex)
{
	int	new_exit_num;

	if (redir == NULL || redir->type != PIPE)
	{
		printf("exit\n");
		ex->quit_program = TRUE;
	}
	if (cmd_array[1] == NULL)
		exit(0);
	new_exit_num = get_new_exit_num(cmd_array[1]);
	if ((cmd_array[2]))
	{
		perror("Too many arguments\n");
		ex->quit_program = FALSE;
		exit(1);
	}
	exit(new_exit_num);
}

static int	get_new_exit_num(char *cmd)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	skip_whitespace(cmd, &i);
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
	{
		if (!(cmd[i] >= '0' && cmd[i] <= '9'))
		{
			perror(cmd);
			exit(255);
		}
		result = (result * 10) + cmd[i] + '0';
		i++;
	}
	return (result);
}
