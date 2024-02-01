/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 04:26:18 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 04:28:42 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	create_process_ids(t_cmd *cmd, t_exec *ex)
{
	int	total_cmds;

	total_cmds = 0;
	while (cmd)
	{
		cmd = cmd->next;
		total_cmds++;
	}
	ex->id = (int *)malloc(sizeof(int) * total_cmds);
	if (!ex->id)
		return ;//MALLOC ERROR
}
