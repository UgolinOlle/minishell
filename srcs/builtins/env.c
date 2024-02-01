/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:10:51 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 16:15:07 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_env(t_exec *ex)
{
	t_list	*env_str;
	int		i;

	env_str = ex->env_list;
	while (env_str)
	{
		i = -1;
		while (((char *)env_str->content)[++i])
		{
			if (((char *)env_str->content)[i] == '=')
				break ;
		}
		if (((char *)env_str->content)[i] == '\0')
		{
			env_str = env_str->next;
			continue ;
		}
		printf("%s\n", ((char *)env_str->content));
		env_str = env_str->next;
	}
	exit (0);
}
