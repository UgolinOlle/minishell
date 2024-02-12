/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:37:59 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 10:29:02 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	initialize_minishell(t_exec *ex, char **env)
{
	int		i;
	int		shlvl;

	ex->cmd = NULL;
	ex->env_list = NULL;
	ex->short_term_data = NULL;
	ex->long_term_data = NULL;
	ex->program_path = NULL;
	ex->total_pipes = 0;
	ex->total_children = 0;
	ex->exit = 0;
	i = -1;
	while (env[++i])
	{
		new_node((void *)env[i], &ex->env_list);
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			ex->program_path = &env[i][4];
	}
	shlvl = change_shlvl(0, ex);
	change_shlvl(2 - shlvl, ex);
}
