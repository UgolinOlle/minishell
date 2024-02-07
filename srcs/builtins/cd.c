/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:13:29 by artclave          #+#    #+#             */
/*   Updated: 2024/02/08 01:34:12 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	free_buffer_and_exit(char *buffer, int exit_code);
static int	update_content(char *var_name, char *new_value, t_list **env_list);
static int	update_env(char *var_name, char *new_env, t_list *env, char *buf);
static void	cd_with_no_arguments(char **new_dir, char *pwd);

void	exec_cd(t_cmd *cmd, char **cmd_array, t_exec *ex)
{
	char	*buffer;
	char	*new_dir;

	while (cmd->redir)
	{
		if (cmd->redir->type == PIPE)
			exit (0);
		cmd->redir = cmd->redir->next;
	}
	buffer = (char *)malloc(sizeof(char) * MAX_PATH_LINUX);
	if (!buffer)
		exit (errno);
	if (getcwd(buffer, MAX_PATH_LINUX) == NULL)
		free_buffer_and_exit(buffer, errno);
	new_dir = cmd_array[1];
	cd_with_no_arguments(&new_dir, buffer);
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(new_dir);
		free_buffer_and_exit(buffer, 1);
	}
	update_env("OLD_PWD=", buffer, ex->env_list, buffer);
	update_env("PWD=", new_dir, ex->env_list, buffer);
	free_buffer_and_exit(buffer, 0);
}

static void	cd_with_no_arguments(char **new_dir, char *pwd)
{
	int	i;
	int	slash_counter;

	if (*new_dir)
		return ;
	*new_dir = pwd;
	i = -1;
	slash_counter = 0;
	while ((*new_dir)[++i] && slash_counter < 3)
	{
		if ((*new_dir)[i] == '/')
			slash_counter++;
		if (slash_counter == 3)
			(*new_dir)[i] = '\0';
	}
}

static int	update_env(char *var_name, char *new_env, t_list *env, char *buf)
{
	int		i;
	char	*next_env;

	i = -1;
	while (env->next)
	{
		next_env = (char *)(env->next->content);
		if (ft_strncmp(var_name, next_env, ft_strlen(var_name)) == 0)
			break ;
		env = env->next;
	}
	if (env == NULL)
		free_buffer_and_exit(buf, errno);
	return (update_content(var_name, new_env, &env));
}

static int	update_content(char *var_name, char *new_value, t_list **env_list)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	len = ft_strlen(var_name) + ft_strlen(new_value);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (EXIT_FAILURE);
	i = -1;
	len = ft_strlen(var_name);
	while (++i < len)
		result[i] = var_name[i];
	j = -1;
	len = ft_strlen(new_value);
	while (++j < len)
		result[i++] = new_value[j];
	result[i] = '\0';
	((*env_list)->content) = (void *)result;
	return (EXIT_SUCCESS);
}

static void	free_buffer_and_exit(char *buffer, int exit_code)
{
	(void)buffer;
	free(buffer);
	exit(exit_code);
}
