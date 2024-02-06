/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 05:36:42 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:36:56 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	open_file(t_redir *redir, int pipe_fd);

void	check_redirections_for_curr_cmd(t_cmd *cmd, t_exec *ex)
{
	int		fd;
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type != PIPE)
		{
			fd = open_file(redir, NO_PIPE);
			if (fd == -1)
			{
				ex->input_error = TRUE;
				perror(redir->file_name);
				return ;
			}
			close(fd);
		}
		redir = redir->next;
	}
}

static int	open_file(t_redir *redir, int pipe_fd)
{
	int	fd;

	fd = -1;
	if (redir->type == PIPE)
		fd = pipe_fd;
	else if (redir->type == INFILE)
		fd = open(redir->file_name, O_RDONLY, 0222);
	else if (redir->type == OUTFILE)
		fd = open(redir->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
		fd = write_heredoc_to_pipe(redir->heredoc_buff);
	return (fd);
}

void	dup_input(t_cmd *cmd, int pipe_fd, t_exec *ex)
{
	t_redir	*redir;
	t_redir	*last_input;
	int		fd;

	last_input = NULL;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->duplication == STDIN_FILENO)
			last_input = redir;
		redir = redir->next;
	}
	if (last_input == NULL)
		return ;
	fd = open_file(last_input, pipe_fd);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ex->input_error = TRUE;
		return ;
	}
	if (last_input->type != PIPE)
		close (fd);
}

void	dup_output(t_cmd *cmd, int pipe_fd, t_exec *ex)
{
	t_redir	*redir;
	t_redir	*last_output;
	int		fd;

	last_output = NULL;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->duplication == STDOUT_FILENO)
			last_output = redir;
		redir = redir->next;
	}
	if (last_output == NULL)
		return ;
	fd = open_file(last_output, pipe_fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ex->input_error = TRUE;
		return ;
	}
	if (last_output->type != PIPE)
		close (fd);
}

void	check_input_error(t_exec *ex)
{
	if (ex->input_error == FALSE)
		return ;
	ex->input_error = TRUE;
	exit (errno);
}
