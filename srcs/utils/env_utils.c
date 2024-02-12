/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 06:24:21 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 09:57:38 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_env_value(char *variable, t_list *env_list)
{
	int		variable_len;
	char	*env;

	variable_len = ft_strlen(variable);
	while (env_list)
	{
		env = ((char *)env_list->content);
		if (ft_strncmp(env, variable, variable_len) == 0)
			return (&env[variable_len]);
		env_list = env_list->next;
	}
	return (NULL);
}

t_list	*get_env_node(char *variable, t_exec *ex)
{
	int		variable_len;
	char	*env;
	t_list	*env_node;

	variable_len = ft_strlen(variable);
	env_node = ex->env_list;
	while (env_node)
	{
		env = ((char *)env_node->content);
		if (ft_strncmp(env, variable, variable_len) == 0)
			return (env_node);
		env_node = env_node->next;
	}
	return (NULL);
}
