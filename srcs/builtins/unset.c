/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:32:23 by artclave          #+#    #+#             */
/*   Updated: 2024/03/09 14:01:04 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check the syntax of the unset command.
 *
 * @param char **array - The command array
 * @return int - EXIT_SUCCESS if the syntax is correct, EXIT_FAILURE otherwise
 */
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
			if (ft_isdigit(array[i][0]) || (!ft_isdigit(array[i][j])
					&& !ft_isalpha(array[i][j]) && array[i][j] != '_'))
			{
				print_error("unset: `", array[i], "': not a valid identifier");
				return (1);
			}
		}
	}
	return (0);
}

/**
 * @brief Delete a node from the list.
 *
 * @param t_list *node_delete - The node to delete
 * @param t_list **head - The head of the list
 * @return void
 */
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

/**
 * @brief Execute the unset command.
 *
 * @param char **cmd_array - The command array
 * @param t_exec *ex - The execution structure
 * @return int - The exit status
 */
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
