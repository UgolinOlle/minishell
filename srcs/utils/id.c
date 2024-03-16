/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:45:11 by artclave          #+#    #+#             */
/*   Updated: 2024/03/07 21:54:39 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_child_ids(t_cmd *cmd, t_exec *ex)
{
	int	i;

	ex->total_children = 0;
	ex->id = NULL;
	while (cmd)
	{
		if (is_builtin(cmd->array[0]) == FALSE)
			ex->total_children++;
		cmd = cmd->next;
	}
	if (ex->total_children == 0)
		return ;
	ex->id = (int *)malloc(sizeof(int) * ex->total_children);
	if (!ex->id)
		return ;
	i = -1;
	while (++i < ex->total_children)
		ex->id[i] = -1;
	add_data_to_cleanup_list((void *)ex->id, &ex->short_term_data);
}