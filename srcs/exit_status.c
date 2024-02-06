/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:26:04 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:22:06 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	get_exit_status(t_exec *ex)
{
	int	exit_status;
	int	child_exit;
	int	i;

	child_exit = 0;
	exit_status = 0;
	i = -1;
	while (++i <= ex->total_pipes)
	{
		waitpid(ex->id[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			child_exit = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			child_exit = WTERMSIG(exit_status);
		ex->exit = child_exit;
	}
	printf("\nexit code: %d\n", ex->exit);
}
