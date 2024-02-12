/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:42:18 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 10:03:17 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_executable_minishell(char *cmd, t_exec *ex)
{
	char	*pwd;
	char	*absolute;
	int		absolute_len;

	pwd = get_env_value("PWD=", ex->env_list);
	if (ft_strncmp(cmd, "./minishell", ft_strlen(cmd)) == 0
		&& ft_strncmp(pwd, ex->program_path, ft_strlen(pwd)) == 0)
		return (TRUE);
	absolute_len = ft_strlen(ex->program_path) + ft_strlen("/minishell");
	absolute = (char *)malloc(sizeof(char) * absolute_len + 1);
	if (!absolute)
		return (FALSE);
	ft_strlcpy(absolute, ex->program_path, ft_strlen(ex->program_path) + 1);
	ft_strcat(absolute, "/minishell\0");
	if (ft_strncmp(cmd, absolute, ft_strlen(cmd)) == 0)
		return (free_data(NULL, absolute, TRUE));
	absolute[ft_strlen(pwd) - 1] = '.';
	if (ft_strncmp(cmd, &absolute[ft_strlen(pwd) - 1], ft_strlen(cmd)) == 0)
		return (free_data(NULL, absolute, TRUE));
	return (free_data(NULL, absolute, FALSE));
}

int	change_shlvl(int change, t_exec *ex)
{
	char	*shlvl_str;
	int		shlvl_num;
	int		i;
	t_list	*env;

	shlvl_str = get_env_value("SHLVL=", ex->env_list);
	shlvl_num = ft_atoi(shlvl_str);
	shlvl_num += change;
	shlvl_str = ft_itoa(shlvl_num);
	env = get_env_node("SHLVL=", ex);
	i = -1;
	while (shlvl_str[++i])
		((char *)env->content)[6 + i] = shlvl_str[i];
	((char *)env->content)[6 + i] = '\0';
	free(shlvl_str);
	return (shlvl_num);
}

void	maybe_increase_shlvl(t_cmd *cmd, t_exec *ex)
{
	if (cmd->next)
		return ;
	if (is_executable_minishell(cmd->array[0], ex) == FALSE)
		return ;
	change_shlvl(+1, ex);
}
