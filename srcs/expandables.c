/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:34:34 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 07:49:55 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <string.h>

int	get_expandable_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '?' && str[i] != ' ')
		i++;
	return (i);
}

void	handle_dollar_sign(t_cmd **cmd_ptr, t_exec *ex)
{
	int		i;
	int		j;
	int		var_len;
	t_cmd	*cmd;

	cmd = *cmd_ptr;
	while (cmd)
	{
		i = 0;
		while (cmd->array[++i])
		{
			j = -1;
			while (cmd->array[i][++j])
			{
				if (cmd->array[i][j] == '$')
				{
					var_len = get_expandable_len(&cmd->array[i][j]);
					sub_expandable(&cmd->array[i], j, var_len, ex);
				}
			}
		}
		cmd = cmd->next;
	}
}

char	*find_env_value(char *str, int len_prefix, int *len_delete, t_exec *ex)
{
	char	*substitute;
	t_list	*env;

	substitute = NULL;
	if ((str)[len_prefix + 1] == '?')
	{
		substitute = ft_itoa(ex->exit);
		*len_delete = 2;
	}
	env = ex->env_list;
	while (!substitute && env)
	{
		if (ft_strncmp(&str[len_prefix + 1], ((char *)env->content),
				*len_delete - 1) == 0)
			substitute = strdup(&((char *)env->content)[*len_delete]);
		env = env->next;
	}
	return (substitute);
}

void	sub_expandable(char **str, int len_prefix, int len_delete, t_exec *ex)
{
	char	*substitute;
	char	*new_str;
	int		new_len;

	substitute = find_env_value(*str, len_prefix, &len_delete, ex);
	if (len_delete == 1)
		return ;
	new_len = ft_strlen(*str) - len_delete + ft_strlen(substitute);
	new_str = (char *)malloc(sizeof(char) * new_len + 1);
	if (substitute)
	{
		strncpy(new_str, *str, len_prefix);
		strcat(new_str, substitute);
		free(substitute);
	}
	else
		strncpy(new_str, *str, len_prefix);
	strcat(new_str, &(*str)[len_prefix + len_delete]);
	new_str[new_len] = '\0';
	free(*str);
	*str = new_str;
}
