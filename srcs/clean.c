/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:12:45 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 06:23:43 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	clean_and_quit_program(t_exec *ex)
{
	clean_list(ex->env_list, FALSE);
	clean_t_cmd(ex->cmd);
	exit(ex->exit);
}
