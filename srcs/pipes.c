/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:36:18 by artclave          #+#    #+#             */
/*   Updated: 2024/02/04 10:25:44 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	create_pipe_fds(t_cmd *cmd, t_exec *ex)
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

void	close_all_pipes(int **fd, int total_pipes)
{
	int	i;
	int	j;

	i = -1;
	while (++i < total_pipes)
	{
		j = -1;
		while (++j < 2)
			close(fd[i][j]);
	}
}

int	write_heredoc_to_pipe(char *buffer)
{
	int	fd[2];
	int	len;

	if (pipe(fd) == -1)
		return (-1);
	len = ft_strlen(buffer);
	write(fd[STDOUT_FILENO], buffer, len);
	close(fd[STDOUT_FILENO]);
	return (fd[STDIN_FILENO]);
}
