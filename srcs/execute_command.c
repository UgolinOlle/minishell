/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 05:35:06 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:25:56 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*get_cmd_path_for_exec(char **cmd_array, char **env);
static void	check_built_ins(t_cmd *cmd, char **cmd_array, t_exec *ex);

void	execute_command(t_cmd *cmd, t_exec *ex)
{
	char	*cmd_path;
	char	**env;

	check_built_ins(cmd, cmd->array, ex);
	env = ft_split(getenv("PATH"), ':');
	cmd_path = get_cmd_path_for_exec(cmd->array, env);
	execve(cmd_path, cmd->array, env);
	perror(cmd->array[0]);
	exit(127);
}

static void	check_built_ins(t_cmd *cmd, char **cmd_array, t_exec *ex)
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
		exec_exit(cmd_array, cmd->redir, ex);
}

static char	*get_cmd_path_for_exec(char **cmd_array, char **env)
{
	char	*test_path;
	int		i;

	i = -1;
	while (env[++i] != NULL)
	{
		test_path = ft_strjoin_with_sep(env[i], cmd_array[0], '/');
		if (access(test_path, F_OK | X_OK) == 0)
			return (test_path);
		else
			free(test_path);
	}
	perror(cmd_array[0]);
	exit(127);
}
