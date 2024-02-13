/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:37:21 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 05:47:44 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_EXEC_H
# define PROCESS_EXEC_H

# include "execution.h"

void	process_cmds(t_cmd *cmd, t_exec *ex);
void	execute_command(int id, int curr_cmd, t_cmd *cmd, t_exec *ex);
void	close_open_pipes(int curr_cmd, t_exec *ex);
void	save_original_io(t_exec *ex);
void	reset_io(t_exec *ex);
void	dup_pipes(int curr_cmd, t_cmd *cmd, t_exec *ex);
void	dup_file_input(t_cmd *cmd);
void	dup_file_output(t_cmd *cmd);
int		are_redirections_valid(t_cmd *cmd);
int		open_file(t_redir *redir, int pipe_fd);

#endif
