/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 06:22:23 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:14:37 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "process_exec.h"
#include "builtin_exec.h"
#include "post_exec.h"
#include "utils_exec.h"

static char	*get_cmd_path_for_exec(char **cmd_array, char **env);

void	process_cmds(t_cmd *cmd, t_exec *ex)
{
	int	curr_cmd;
	int	curr_child;

	curr_cmd = 0;
	curr_child = 0;
	while (cmd)
	{
		save_original_io(ex);
		dup_pipes(curr_cmd, cmd, ex);
		dup_file_input(cmd);
		dup_file_output(cmd);
		if (is_builtin(cmd->array[0]) == TRUE)
			execute_builtin(cmd, ex);
		else
		{
			execute_command(ex->id[curr_child], curr_cmd, cmd, ex);
			curr_child++;
		}
		curr_cmd++;
		reset_io(ex);
		cmd = cmd->next;
	}
}

void	execute_command(int id, int curr_cmd, t_cmd *cmd, t_exec *ex)
{
	char	*cmd_path;
	char	**env;

	id = fork();
	if (id == -1)
		return ;
	if (id == 0)
	{
		close_open_pipes(curr_cmd, ex);
		if (are_redirections_valid(cmd) == EXIT_FAILURE)
			exit(1);
		if (is_executable_minishell(cmd->array[0], ex) == TRUE)
			exit(0);
		env = ft_split(get_env_value("PATH=", ex->env_list), ':');
		cmd_path = get_cmd_path_for_exec(cmd->array, env);
		execve(cmd_path, cmd->array, env);
		perror(cmd->array[0]);
		exit(127);
	}
}

static char	*get_cmd_path_for_exec(char **cmd_array, char **env)
{
	char	*test_path;
	int		i;

	i = -1;
	if (access(cmd_array[0], F_OK | X_OK) == 0)
		return (cmd_array[0]);
	while (env[++i] != NULL)
	{
		test_path = ft_strjoin_with_sep(env[i], cmd_array[0], '/');
		if (access(test_path, F_OK | X_OK) == 0)
			return (test_path);
		else
			free(test_path);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_array[0], 2);
	if (ft_strchr(cmd_array[0], '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
	return (NULL);
}
