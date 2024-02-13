/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:32:23 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:11:19 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin_exec.h"
#include "utils_exec.h"

static int	check_unset_syntax(char **cmd_array);
static void	delete_node(t_list *node_delete, t_list **head);

int	exec_unset(char **cmd_array, t_exec *ex)
{
	int		i;
	t_list	*env_node;

	if (has_pipe(ex->cmd))
		return (0);
	if (check_unset_syntax(cmd_array) == EXIT_FAILURE)
		return (1);
	i = 0;
	while (cmd_array[++i])
	{
		env_node = get_env_node(cmd_array[i], ex);
		delete_node(env_node, &ex->env_list);
	}
	return (0);
}

static int	check_unset_syntax(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			if (is_digit(array[i][0]) || (!is_digit(array[i][j])
				&& !is_letter(array[i][j]) && array[i][j] != '_'))
			{
				print_error("unset: `", array[i], "': not a valid identifier");
				return (1);
			}
		}
	}
	return (0);
}

static void	delete_node(t_list *node_delete, t_list **head)
{
	t_list	*list;

	if (node_delete == NULL)
		return ;
	list = *head;
	if (list == node_delete)
	{
		list = node_delete->next;
		free(node_delete);
		return ;
	}
	while (list)
	{
		if (list->next == node_delete)
		{
			list->next = list->next->next;
			free(node_delete);
			return ;
		}
		list = list->next;
	}
}
