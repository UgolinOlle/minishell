/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:13:41 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 10:06:26 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	check_unset_syntax(char **cmd_array);
static void	delete_node(t_list *node_delete, t_list **head);

void	exec_unset(char **cmd_array, t_exec *ex)
{
	int		i;
	t_list	*env_node;
	char	*env_str;

	check_unset_syntax(cmd_array);
	i = 0;
	while (cmd_array[++i])
	{
		env_node = ex->env_list;
		while (env_node)
		{
			env_str = ((char *)env_node->content);
			if (ft_strncmp(cmd_array[i], env_str, ft_strlen(cmd_array[i])) == 0)
			{
				delete_node(env_node, &ex->env_list);
				break ;
			}
			env_node = env_node->next;
		}
	}
	exit(0);
}

static void	check_unset_syntax(char **cmd_array)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_array[++i])
	{
		j = -1;
		while (cmd_array[i][++j])
		{
			if (is_digit(cmd_array[i][0]) || (!is_letter(cmd_array[i][j])
					&& !is_digit(cmd_array[i][j]) && cmd_array[i][j] != '_'))
			{
				perror(cmd_array[i]);
				exit (1);
			}
		}
	}
}

static void	delete_node(t_list *node_delete, t_list **head)
{
	t_list	*list;

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
