/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:34:17 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 05:40:59 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREP_EXEC_H
# define PREP_EXEC_H

# include "execution.h"

void	initialize_minishell(t_exec *ex, char **env);
void	execution_main(t_exec *ex);
void	handle_dollar_sign(t_cmd **cmd_ptr, t_exec *ex);
void	create_pipes(t_cmd *cmd, t_exec *ex);
void	create_child_ids(t_cmd *cmd, t_exec *ex);

#endif
