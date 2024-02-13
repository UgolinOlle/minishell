/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:50:45 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:11:59 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "utils_exec.h"

void	new_node(void *content, t_list **list)
{
	t_list	*new_node;
	t_list	*prev_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = content;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		prev_node = get_last_node(*list);
		prev_node->next = new_node;
	}
}

t_list	*get_last_node(t_list *list)
{
	while (list->next)
		list = list->next;
	return (list);
}
