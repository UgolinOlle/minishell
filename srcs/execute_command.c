/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 05:35:06 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 11:44:46 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_command(t_cmd *cmd, t_exec *ex)
{
	char	*cmd_path;
	char	**env;

	(void)ex;
	//check for envp expandables(cmd->array) //maybe use realloc
	check_built_ins(cmd, cmd->array, ex);
	env = ft_split(getenv("PATH"), ':');
	cmd_path = get_cmd_path_for_exec(cmd->array, env);
	execve(cmd_path, cmd->array, env);
	perror(cmd->array[0]);
	exit(127);
}

char	*get_cmd_path_for_exec(char **cmd_array, char **env)
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
