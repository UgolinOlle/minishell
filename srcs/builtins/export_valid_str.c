/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_valid_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:37:39 by artclave          #+#    #+#             */
/*   Updated: 2024/02/07 04:25:57 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	is_variable_start_valid(char *cmd_array, char *original_cmd)
{
	int	j;

	j = 0;
	skip_whitespace(cmd_array, &j);
	if (!is_letter(cmd_array[j]) && cmd_array[j] != '_')
	{
		ft_putstr_fd("minishell: export `", 2);
		ft_putstr_fd(cmd_array, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		free(original_cmd);
		exit(1);
	}
}

void	is_variable_content_valid(char *cmd_array, char *original_cmd)
{
	int	j;

	j = 0;
	skip_whitespace(cmd_array, &j);
	while (cmd_array[j] && cmd_array[j] != '=')
	{
		if (!is_letter(cmd_array[j]) && !is_digit(cmd_array[j])
			&& cmd_array[j] != '_')
		{
			ft_putstr_fd("minishell: export `", 2);
			ft_putstr_fd(cmd_array, 2);
			ft_putstr_fd("': not a valid identifier", 2);
			free(original_cmd);
			exit(1);
		}
		j++;
	}
}
