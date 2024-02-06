/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:55:16 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:30:54 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	next_smallest_string(t_list *env, char *new_min, char *old_min);

void	print_env_alphabetically(t_list *env, t_list *head)
{
	char	*new_min;
	char	*old_min;

	new_min = ((char *)env->content);
	old_min = NULL;
	while (1)
	{
		env = head;
		if (old_min)
			new_min = NULL;
		while (env)
		{
			if (next_smallest_string(env, new_min, old_min))
				new_min = ((char *)env->content);
			env = env->next;
		}
		if (new_min == NULL)
			break ;
		printf("declare -x %s\n", new_min);
		old_min = new_min;
	}
}

static int	next_smallest_string(t_list *env, char *new_min, char *old_min)
{
	char	*next_str;
	int		len;

	next_str = ((char *)env->content);
	len = ft_strlen(next_str);
	if (!new_min || ft_strncmp(next_str, new_min, len) < 0)
	{
		if (!old_min || ft_strncmp(next_str, old_min, len) > 0)
			return (TRUE);
	}
	return (FALSE);
}
