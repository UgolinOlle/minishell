/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 07:19:13 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:14:48 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "post_exec.h"

void	wait_for_child_exit_status(t_exec *ex)
{
	int	exit_status;
	int	child_exit;
	int	curr_child;

	curr_child = -1;
	while (++curr_child < ex->total_children)
	{
		waitpid(ex->id[curr_child], &exit_status, 0);
		if (WIFEXITED(exit_status))
			child_exit = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			child_exit = WTERMSIG(exit_status);
		if (ex->is_builtin_last == FALSE)
			ex->exit = child_exit;
	}
}
