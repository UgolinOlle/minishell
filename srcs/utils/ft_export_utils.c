/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:58:52 by artclave          #+#    #+#             */
/*   Updated: 2024/03/09 21:38:32 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_smallest_string(t_list *env, char *new_min, char *old_min);

int	is_variable_start_valid(char *cmd_array, char *original_cmd)
{
	int	j;

	j = 0;
	skip_whitespace(cmd_array, &j);
	if (!ft_isalpha(cmd_array[j]) && cmd_array[j] != '_')
	{
		print_error("export `", cmd_array, "': not a valid identifier");
		return (free_data(NULL, original_cmd, 1));
	}
	return (0);
}

int	is_variable_content_valid(char *cmd_array, char *original_cmd)
{
	int	j;

	j = 0;
	skip_whitespace(cmd_array, &j);
	while (cmd_array[j] && cmd_array[j] != '=')
	{
		if (!ft_isalpha(cmd_array[j]) && !ft_isnum(cmd_array[j])
			&& cmd_array[j] != '_')
		{
			print_error("export `", cmd_array, "': not a valid identifier");
			return (free_data(NULL, original_cmd, 1));
		}
		j++;
	}
	return (0);
}

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
