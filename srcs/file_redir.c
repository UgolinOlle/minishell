/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:41:34 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:15:23 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "process_exec.h"

static int	write_heredoc_to_pipe(char *buffer);

void	dup_file_input(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;
	t_redir	*last_input;

	last_input = NULL;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->duplication == STDIN_FILENO)
			last_input = redir;
		redir = redir->next;
	}
	if (last_input && last_input->type != PIPE)
	{
		fd = open_file(last_input, NO_PIPE);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	dup_file_output(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;
	t_redir	*last_output;

	last_output = NULL;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->duplication == STDOUT_FILENO)
			last_output = redir;
		redir = redir->next;
	}
	if (last_output && last_output->type != PIPE)
	{
		fd = open_file(last_output, NO_PIPE);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

int	are_redirections_valid(t_cmd *cmd)
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
				perror(redir->file_name);
				return (1);
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

int	open_file(t_redir *redir, int pipe_fd)
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

static int	write_heredoc_to_pipe(char *buffer)
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
