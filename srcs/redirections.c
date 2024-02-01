/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 05:36:42 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 04:12:52 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	check_redirections_for_curr_cmd(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type != PIPE)
		{
			fd = open_file(redir, NO_PIPE);
			close(fd);
		}
		redir = redir->next;
	}
}

void	dup_input(t_cmd *cmd, int pipe_fd)
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
		perror("Error using dup2\n");
		exit(errno);
	}
	if (last_input->type != PIPE)
		close (fd);
}

void	dup_output(t_cmd *cmd, int pipe_fd)
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
		perror("Error using dup2\n");
		exit(errno);
	}
	if (last_output->type != PIPE)
		close (fd);
}

int	open_file(t_redir *redir, int pipe_fd)
{
	int	fd;

	fd = -1;
	if (redir->type == PIPE)
		fd = pipe_fd;
	else if (redir->type == INFILE)
		fd = open(redir->file.name, O_RDONLY, 0222);
	else if (redir->type == OUTFILE)
		fd = open(redir->file.name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file.name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
		fd = write_heredoc_to_pipe(redir->file.heredoc_buff);
	if (fd == -1 && redir->type != PIPE)
	{
		perror(redir->file.name);
		exit(1);
	}
	if (fd == -1 && redir->type == PIPE)
	{
		perror("Error creating pipe\n");
		exit(errno);
	}
	return (fd);
}
