/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:47:14 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 14:42:29 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (TRUE);
	return (FALSE);
}

void	execute_builtin(t_cmd *cmd, t_exec *ex)
{
	int	exit_code;

	ex->is_builtin_last = FALSE;
	if (ft_strncmp(cmd->array[0], "cd", ft_strlen(cmd->array[0])) == 0)
		exit_code = exec_cd(cmd->array, cmd, ex);
	else if (ft_strncmp(cmd->array[0], "echo", ft_strlen(cmd->array[0])) == 0)
		exit_code = exec_echo(cmd->array);
	else if (ft_strncmp(cmd->array[0], "env", ft_strlen(cmd->array[0])) == 0)
		exit_code = exec_env(ex);
	else if (ft_strncmp(cmd->array[0], "exit", ft_strlen(cmd->array[0])) == 0)
		exit_code = exec_exit(cmd->array, cmd);
	else if (ft_strncmp(cmd->array[0], "export", ft_strlen(cmd->array[0])) == 0)
		exit_code = exec_export(cmd->array, ex);
	else if (ft_strncmp(cmd->array[0], "pwd", ft_strlen(cmd->array[0])) == 0)
		exit_code = exec_pwd(ex);
	else if (ft_strncmp(cmd->array[0], "unset", ft_strlen(cmd->array[0])) == 0)
		exit_code = exec_unset(cmd->array, ex);
	if (!cmd->next)
	{
		ex->is_builtin_last = TRUE;
		ex->exit = exit_code;
	}
}
