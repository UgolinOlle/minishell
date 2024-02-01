/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:09:23 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 11:13:31 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	check_built_ins(t_cmd *cmd, char **cmd_array, t_exec *ex)
{
	if (ft_strncmp(cmd_array[0], "echo", ft_strlen("echo")) == 0)
		exec_echo(cmd_array);
	else if (ft_strncmp(cmd_array[0], "cd", ft_strlen("cd")) == 0)
		exec_cd(cmd, cmd_array, ex);
	else if (ft_strncmp(cmd_array[0], "pwd", ft_strlen("pwd")) == 0)
		exec_pwd();
	else if (ft_strncmp(cmd_array[0], "export", ft_strlen("export")) == 0)
		exec_export(cmd_array, ex);
	else if (ft_strncmp(cmd_array[0], "unset", ft_strlen("unset")) == 0)
		exec_unset(cmd_array, ex);
	else if (ft_strncmp(cmd_array[0], "env", ft_strlen("env")) == 0)
		exec_env(ex);
	else if (ft_strncmp(cmd_array[0], "exit", ft_strlen("exit")) == 0)
		exec_exit(cmd_array, ex);
}
