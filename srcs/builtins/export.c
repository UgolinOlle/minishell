/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:46:56 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 14:39:54 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_export_syntax_valid(char **cmd_array, char *original_cmd);

int	exec_export(char **cmd_array, t_exec *ex)
{
	int		i;
	char	*original_cmd_str;
	char	*new_value;
	int		error;

	if (has_pipe(ex->cmd) == TRUE && cmd_array[1])
		return (0);
	i = 0;
	while (cmd_array[++i])
	{
		original_cmd_str = ft_strdup(cmd_array[i]);
		error = is_export_syntax_valid(&cmd_array[i], original_cmd_str);
		if (error > 0)
			return (error);
		new_value = ft_strdup(cmd_array[i]);
		new_node((void *)new_value, &ex->env_list);
		add_data_to_cleanup_list(new_value, &ex->long_term_data);
	}
	if (!cmd_array[1])
		print_env_alphabetically(ex->env_list, ex->env_list);
	return (free_data(NULL, original_cmd_str, 0));
}

static int	is_export_syntax_valid(char **cmd_array, char *original_cmd)
{
	int	error;

	error = has_unclosed_quotes(*cmd_array, original_cmd);
	if (error > 0)
		return (error);
	delete_outside_quotes(cmd_array);
	error = is_variable_start_valid(*cmd_array, original_cmd);
	if (error > 0)
		return (error);
	error = is_variable_content_valid(*cmd_array, original_cmd);
	if (error > 0)
		return (error);
	add_slash_to_inside_double_quotes(cmd_array, ft_strlen(*cmd_array));
	add_quotes_around_value(cmd_array);
	return (0);
}
