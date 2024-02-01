/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_valid_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:37:39 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 16:02:12 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_variable_start_valid(char *cmd_array, char *original_cmd)
{
	int	j;

	j = 0;
	skip_whitespace(cmd_array, &j);
	if (!is_letter(cmd_array[j]) && cmd_array[j] != '_')
	{
		perror(original_cmd);
		free(original_cmd);
		return (FALSE);
	}
	return (TRUE);
}

int	is_variable_content_valid(char *cmd_array, char *original_cmd)
{
	int	j;

	j = 0;
	skip_whitespace(cmd_array, &j);
	while (cmd_array[j] && cmd_array[j] != '=')
	{
		if (!is_letter(cmd_array[j]) && !is_digit(cmd_array[j])
			&& cmd_array[j] != '_')
		{
			perror(original_cmd);
			free(original_cmd);
			return (FALSE);
		}
		j++;
	}
	return (TRUE);
}
