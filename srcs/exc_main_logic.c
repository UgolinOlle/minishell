/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_main_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 05:28:56 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 15:43:58 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution(t_exec *ex)
{
	t_list	*id_list;
	t_cmd	*cmd;

	cmd = ex->cmd;
	id_list = NULL;
	handle_dollar_sign(&ex->cmd, ex);
	create_pipe_fds(cmd, ex);
	create_process_ids(cmd, ex);
	check_redirections_for_curr_cmd(cmd);
	dup_input(cmd, NO_PIPE);
	while (cmd->next)
	{
		piped_commands(cmd, ex);
		cmd = cmd->next;
	}
	last_command(cmd, ex);
	get_exit_status(ex);
}

void	piped_commands(t_cmd *cmd, t_exec *ex)
{
	static int	curr_pipe;
	int			curr_cmd;
	int			**fd;

	fd = ex->fd;
	curr_cmd = curr_pipe;
	ex->id[curr_cmd] = fork();
	if (ex->id[curr_cmd] == -1)
		return ;//HANDLE ERROR
	if (ex->id[curr_cmd] == 0)
	{
		dup_output(cmd, fd[curr_pipe][STDOUT_FILENO]);
		close_all_pipes(ex->fd, ex->total_pipes);
		execute_command(cmd, ex);
	}
	else
	{
		check_redirections_for_curr_cmd(cmd->next);
		dup_input(cmd->next, fd[curr_pipe][STDIN_FILENO]);
		curr_pipe++;
		if (!cmd->next->next)
			curr_pipe = 0;
	}
}

void	last_command(t_cmd *cmd, t_exec *ex)
{
	int	last_cmd;

	last_cmd = ex->total_pipes;
	ex->id[last_cmd] = fork();
	if (ex->id[last_cmd] == -1)
		return ;//HANDLE ERROR
	if (ex->id[last_cmd] == 0)
	{
		dup_output(cmd, NO_PIPE);
		close_all_pipes(ex->fd, ex->total_pipes);
		execute_command(cmd, ex);
	}
	else
		close_all_pipes(ex->fd, ex->total_pipes);
}
