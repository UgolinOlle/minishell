/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:13:56 by artclave          #+#    #+#             */
/*   Updated: 2024/01/29 02:09:38 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_pwd(void)
{
	char	*buff;

	buff = (char *)malloc(sizeof(char) * MAX_PATH_LINUX);
	if (!buff)
		return ; //HANDLE ERROR
	if (getcwd(buff, MAX_PATH_LINUX) == NULL)
		return ; //HANDLE ERROR BUFFER TOO SMALL
	printf("%s\n", buff);
	free(buff);
	exit (0);
}
