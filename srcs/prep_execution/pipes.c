/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:43:48 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:19:50 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "prep_exec.h"
#include "post_exec.h"

void	create_pipes(t_cmd *cmd, t_exec *ex)
{
	int	i;

	if (!cmd->next)
		return ;
	ex->total_pipes = 0;
	while (cmd->next)
	{
		ex->total_pipes++;
		cmd = cmd->next;
	}
	ex->fd = (int **)malloc(sizeof(int *) * ex->total_pipes);
	if (!ex->fd)
		return ;
	add_data_to_cleanup_list((void *)ex->fd, &ex->short_term_data);
	i = -1;
	while (++i < ex->total_pipes)
	{
		ex->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!ex->fd[i] || pipe(ex->fd[i]) == -1)
			return ;
		add_data_to_cleanup_list((void *)ex->fd[i], &ex->short_term_data);
	}
}

void	dup_pipes(int current, t_cmd *cmd, t_exec *ex)
{
	(void)ex;
	if (current > 0)
	{
		dup2(ex->fd[current - 1][STDIN_FILENO], STDIN_FILENO);
		close(ex->fd[current - 1][STDIN_FILENO]);
	}
	if (cmd->next)
	{
		dup2(ex->fd[current][STDOUT_FILENO], STDOUT_FILENO);
		close(ex->fd[current][STDOUT_FILENO]);
	}
}

void	close_open_pipes(int curr_cmd, t_exec *ex)
{
	int	i;

	if (curr_cmd == ex->total_pipes)
		return ;
	close(ex->fd[curr_cmd][STDIN_FILENO]);
	i = curr_cmd;
	while (++i < ex->total_pipes)
	{
		close(ex->fd[i][STDIN_FILENO]);
		close(ex->fd[i][STDOUT_FILENO]);
	}
}
