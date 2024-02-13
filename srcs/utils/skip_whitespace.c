/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:30:16 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:12:04 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "utils_exec.h"

void	skip_whitespace(char *str, int *i)
{
	if (!str)
		return ;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}
