/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:34:34 by artclave          #+#    #+#             */
/*   Updated: 2024/02/08 01:35:11 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	get_expandable_len(char *str);
static void	sub_expandable(char **str, int prefix, int delete, t_exec *ex);
static char	*find_env_value(char *str, int prefix, int *delete, t_exec *ex);

void	handle_dollar_sign(t_cmd **cmd_ptr, t_exec *ex)
{
	int		i;
	int		j;
	int		var_len;
	t_cmd	*cmd;

	cmd = *cmd_ptr;
	while (cmd)
	{
		i = -1;
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

static int	get_expandable_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '?' && str[i] != ' ')
		i++;
	return (i);
}

static void	sub_expandable(char **str, int prefix, int delete, t_exec *ex)
{
	char	*substitute;
	char	*new_str;
	int		new_len;

	(void)ex;
	substitute = find_env_value(*str, prefix, &delete, ex);
	if (delete == 1)
		return ;
	new_len = ft_strlen(*str) - delete + ft_strlen(substitute);
	new_str = (char *)malloc(sizeof(char) * new_len + 1);
	if (substitute)
	{
		printf("hey\n");
		ft_strlcpy(new_str, *str, prefix + 1);
		ft_strcat(new_str, substitute);
		free(substitute);
	}
	else
		ft_strlcpy(new_str, *str, prefix + 1);
	ft_strcat(new_str, &(*str)[prefix + delete]);
	free(*str);
	*str = new_str;
}

static char	*find_env_value(char *str, int prefix, int *delete, t_exec *ex)
{
	char	*substitute;
	t_list	*env;

	substitute = NULL;
	if (*delete == 1)
		return (substitute);
	if ((str)[prefix + 1] == '?')
	{
		substitute = ft_itoa(ex->exit);
		*delete = 2;
	}
	env = ex->env_list;
	while (!substitute && env)
	{
		if (ft_strncmp(&str[prefix + 1], ((char *)env->content),
				*delete - 1) == 0)
			substitute = ft_strdup(&((char *)env->content)[*delete]);
		env = env->next;
	}
	return (substitute);
}
