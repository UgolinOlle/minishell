/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:40:39 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 05:48:47 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_EXEC_H
# define BUILTIN_EXEC_H

# include "execution.h"

int		is_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, t_exec *ex);
//cd
int		exec_cd(char **cmd_array, t_cmd *cmd, t_exec *ex);
//echo
int		exec_echo(char **cmd_array);
//env
int		exec_env(t_exec *ex);
//exit
int		exec_exit(char **cmd_array, t_cmd *cmd);
//export
int		exec_export(char **cmd_array, t_exec *ex);
int		has_unclosed_quotes(char *str, char *cmd);
void	delete_outside_quotes(char **str);
void	add_slash_to_inside_double_quotes(char **str, int len);
void	add_quotes_around_value(char **str);
int		is_variable_start_valid(char *cmd_array, char *original_cmd);
int		is_variable_content_valid(char *cmd_array, char *original_cmd);
void	print_env_alphabetically(t_list *env, t_list *head);
//pwd
int		exec_pwd(t_exec *ex);
//unset
int		exec_unset(char **cmd_array, t_exec *ex);

#endif
