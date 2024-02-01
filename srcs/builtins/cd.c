/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:13:29 by artclave          #+#    #+#             */
/*   Updated: 2024/01/29 08:59:07 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_cd(t_cmd *cmd, char **cmd_array, t_exec *ex)
{
	char	*buffer;
	char	*new_dir;

	//get dollar sign expandables
	//check if new dir is correct
	while (cmd->redir)
	{
		if (cmd->redir->type == PIPE)
			exit (0);
		cmd->redir = cmd->redir->next;
	}
	buffer = (char *)malloc(sizeof(char) * MAX_PATH_LINUX);
	if (!buffer)
		return ;//HANDLE ERROR
	if (getcwd(buffer, MAX_PATH_LINUX) == NULL)
		return ;//HANDLE ERROR BUFFER TOO SMALL
	new_dir = cmd_array[1];
	cd_with_no_arguments(&new_dir, buffer);
	chdir(new_dir);
	update_env("OLD_PWD=", buffer, ex->env_list);
	update_env("PWD=", new_dir, ex->env_list);
	exec_pwd(); //FOR CHECKING IT IS UPDATED
	free(buffer);
	exit(0);
}

void	cd_with_no_arguments(char **new_dir, char *pwd)
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

void	update_env(char *var_name, char *new_env, t_list *env_list)
{
	int		i;
	char	*next_env;

	i = -1;
	while (env_list->next)
	{
		next_env = (char *)(env_list->next->content);
		if (ft_strncmp(var_name, next_env, ft_strlen(var_name)) == 0)
			break ;
		env_list = env_list->next;
	}
	if (env_list == NULL)
		return ;//ERROR OLD PATH NOT FOUND
	update_node_content(var_name, new_env, &env_list);
}

void	update_node_content(char *var_name, char *new_value, t_list **env_list)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	len = ft_strlen(var_name) + ft_strlen(new_value);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return ;//ERROR MALLOC
	i = -1;
	len = ft_strlen(var_name);
	while (++i < len)
		result[i] = var_name[i];
	j = -1;
	len = ft_strlen(new_value);
	while (++j < len)
		result[i++] = new_value[j];
	result[i] = '\0';
	//ADD TO CLEAN UPON ERROR
	((*env_list)->content) = (void *)result;
}
