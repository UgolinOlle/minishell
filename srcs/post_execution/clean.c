/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:12:45 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:12:37 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "post_exec.h"
#include "utils_exec.h"

void	exit_minishell(t_exec *ex, int exit_num)
{
	clean_t_cmd(ex->cmd);
	clean_list(ex->env_list, FALSE);
	clean_list(ex->shell_env_list, FALSE);
	clean_list(ex->short_term_data, TRUE);
	clean_list(ex->long_term_data, TRUE);
	exit(exit_num);
}

void	maybe_quit_program(t_exec *ex)
{
	if (ex->cmd->next)
		return ;
	if (ft_strncmp(ex->cmd->array[0], "exit", ft_strlen("exit")) != 0)
		return ;
	if (!(ex->cmd->array[1] == NULL
			|| !str_is_numerical(ex->cmd->array[1])
			|| (str_is_numerical(ex->cmd->array[1])
				&& ex->cmd->array[2] == NULL)))
		return ;
	if (change_shlvl(-1, ex) > 1)
		get_previous_shells_env(ex);
	exit_minishell(ex, ex->exit);
}

void	clean_list(t_list *list, int clean_content)
{
	t_list	*temp;

	while (list)
	{
		temp = list->next;
		if (clean_content == TRUE)
			free(list->content);
		free(list);
		list = temp;
	}
}

void	clean_t_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp_cmd;
	t_redir	*temp_redir;

	while (cmd)
	{
		i = -1;
		while (cmd->redir)
		{
			temp_redir = cmd->redir->next;
			free(cmd->redir);
			cmd->redir = temp_redir;
		}
		while (cmd->array[++i])
			free(cmd->array[i]);
		free(cmd->array);
		temp_cmd = cmd->next;
		free(cmd);
		cmd = temp_cmd;
	}
}

void	add_data_to_cleanup_list(void *content, t_list **list)
{
	t_list	*node;

	node = NULL;
	if (!content)
		return ;
	new_node(content, &node);
	node->next = (*list);
	(*list) = node;
}
