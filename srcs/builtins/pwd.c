/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:13:56 by artclave          #+#    #+#             */
/*   Updated: 2024/02/04 04:53:38 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_pwd(void)
{
	char	*buff;

	buff = (char *)malloc(sizeof(char) * MAX_PATH_LINUX);
	if (!buff)
		exit(errno);
	if (getcwd(buff, MAX_PATH_LINUX) == NULL)
	{
		free(buff);
		exit(errno);
	}
	printf("%s\n", buff);
	free(buff);
	exit (0);
}
