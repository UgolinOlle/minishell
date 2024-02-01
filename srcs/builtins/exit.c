/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:10:06 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 16:04:02 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_exit(char **cmd_array, t_exec *ex)
{
	int	i;
	int	new_exit_num;

	if (cmd_array[1] == NULL)
		exit(ex->exit); //actually quit program!!
	//HANDLE ENV $
	i = 0;
	new_exit_num = 0;
	skip_whitespace(cmd_array[1], &i);
	while (cmd_array[1][i] && cmd_array[1][i] != ' ' && cmd_array[1][i] != '\t')
	{
		if (!(cmd_array[1][i] >= '0' && cmd_array[1][i] <= '9'))
		{
			perror(cmd_array[1]);
			exit(255);//actualqly quit program!!
		}
		new_exit_num = (new_exit_num * 10) + cmd_array[1][i] + '0';
		i++;
	}
	if ((cmd_array[2]))
	{
		perror("Too many arguments\n");
		exit(1); //DO NOOTTTT QUIT PROGRAM!!!
	}
	exit(new_exit_num); //ACTUALLY QUIT PROGROM
}
