/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 07:03:24 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 10:07:17 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	save_original_io(t_exec *ex)
{
	ex->stdin_original = dup(STDIN_FILENO);
	ex->stdout_original = dup(STDOUT_FILENO);
}

void	reset_io(t_exec *ex)
{
	dup2(ex->stdin_original, STDIN_FILENO);
	close(ex->stdin_original);
	dup2(ex->stdout_original, STDOUT_FILENO);
	close(ex->stdout_original);
}
