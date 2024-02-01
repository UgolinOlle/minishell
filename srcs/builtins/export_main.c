/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:11:31 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 12:07:19 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_export(char **cmd_array, t_exec *ex)
{
	int		i;
	char	*original_cmd_str;

	while (ex->cmd->redir)
	{
		if (ex->cmd->redir->type == PIPE)
			exit (0);
		ex->cmd->redir = ex->cmd->redir->next;
	}
	i = 0;
	while (cmd_array[++i])
	{
		original_cmd_str = ft_strdup(cmd_array[i]);
		is_export_syntax_valid(cmd_array[i], original_cmd_str);
		new_node(ft_strdup((void *)cmd_array[i]), &ex->env_list);
		free(original_cmd_str);
	}
	if (!cmd_array[1])
		print_env_alphabetically(ex->env_list, ex->env_list);
	exit(0);
}

int	is_export_syntax_valid(char *cmd_array, char *original_cmd)
{
	if (has_unclosed_quotes(cmd_array, original_cmd))
		return (FALSE);
	delete_outside_quotes(&cmd_array);
	if (!is_variable_start_valid(cmd_array, original_cmd))
		return (FALSE);
	if (!is_variable_content_valid(cmd_array, original_cmd))
		return (FALSE);
	add_slash_to_inside_double_quotes(&cmd_array, ft_strlen(cmd_array));
	add_quotes_around_value(&cmd_array);
	return (TRUE);
}
