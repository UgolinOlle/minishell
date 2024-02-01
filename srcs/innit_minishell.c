/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:03:11 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 04:16:34 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	initialize_minishell(t_exec *ex, char **env)
{
	int		i;

	ex->cmd = NULL;
	ex->exit = 0;
	ex->id_list = NULL;
	ex->env_list = NULL;
	ex->total_pipes = 0;
	i = -1;
	while (env[++i])
		new_node((void *)env[i], &ex->env_list);
}
