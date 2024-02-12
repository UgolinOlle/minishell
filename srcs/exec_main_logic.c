/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_logic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:36:31 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 14:37:27 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution_main(t_exec *ex)
{
	t_cmd	*cmd;

	cmd = ex->cmd;
	handle_dollar_sign(&ex->cmd, ex);
	create_pipes(cmd, ex);
	create_child_ids(cmd, ex);
	process_cmds(cmd, ex);
	wait_for_child_exit_status(ex);
	maybe_increase_shlvl(cmd, ex);
	maybe_quit_program(ex);
	clean_list(ex->short_term_data, TRUE);
	clean_t_cmd(ex->cmd);
}
