/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:43:12 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 06:40:57 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_EXEC_H
# define POST_EXEC_H

# include "execution.h"

//PART 3: SHLVL
int		is_executable_minishell(char *cmd, t_exec *ex);
int		change_shlvl(int change, t_exec *ex);
void	adjust_shlvl(t_cmd *cmd, t_exec *ex);
void	get_previous_shells_env(t_exec *ex);

//PART 3: POST
void	wait_for_child_exit_status(t_exec *ex);
void	maybe_quit_program(t_exec *ex);
void	exit_minishell(t_exec *ex, int exit_num);

//PART 3: CLEAN
void	clean_list(t_list *list, int clean_content);
void	clean_t_cmd(t_cmd *cmd);
void	add_data_to_cleanup_list(void *content, t_list **list);

#endif
