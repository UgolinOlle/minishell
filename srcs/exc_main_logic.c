/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_main_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 05:28:56 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 04:05:45 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution(t_exec *ex)
{
	t_cmd	*cmd;

	cmd = ex->cmd;
	ex->quit_program = TRUE;
	handle_dollar_sign(&ex->cmd, ex);
	create_pipe_fds(cmd, ex);
	create_process_ids(cmd, ex);
	check_redirections_for_curr_cmd(cmd, ex);
	dup_input(cmd, NO_PIPE, ex);
	while (cmd->next)
	{
		piped_commands(cmd, ex);
		cmd = cmd->next;
	}
	last_command(cmd, ex);
	get_exit_status(ex);
	clean_list(ex->short_term_data, TRUE);
	if (ex->quit_program == TRUE)
		clean_and_quit_program(ex);
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
		return ;
	if (ex->id[curr_cmd] == 0)
	{
		check_input_error(ex);
		dup_output(cmd, fd[curr_pipe][STDOUT_FILENO], ex);
		close_all_pipes(ex->fd, ex->total_pipes);
		execute_command(cmd, ex);
	}
	else
	{
		check_redirections_for_curr_cmd(cmd->next, ex);
		dup_input(cmd->next, fd[curr_pipe][STDIN_FILENO], ex);
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
		return ;
	if (ex->id[last_cmd] == 0)
	{
		check_input_error(ex);
		dup_output(cmd, NO_PIPE, ex);
		close_all_pipes(ex->fd, ex->total_pipes);
		execute_command(cmd, ex);
	}
	else
		close_all_pipes(ex->fd, ex->total_pipes);
}
