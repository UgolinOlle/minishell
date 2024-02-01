/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:34:34 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 16:14:08 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_dollar_sign(t_cmd **cmd, t_exec *ex)
{
	int	i;
	int	j;
	int	start;

	while (*cmd)
	{
		i = 0;
		while ((*cmd)->array[++i])
		{
			j = -1;
			while ((*cmd)->array[i][++j])
			{
				if ((*cmd)->array[i][j] == '$')
				{
					start = ++j;
					while ((*cmd)->array[i][j] && (*cmd)->array[i][j] != '=')
						j++;
					sub_expandable(&(*cmd)->array[i], start, j - start + 1, ex);
					j = start;
				}
			}
		}
		*cmd = (*cmd)->next;
	}
}

void	sub_expandable(char **str, int start, int end, t_exec *ex)
{
	char	*new_str1;
	char	*new_str2;
	t_list	*env;

	env = ex->env_list;
	while (env)
	{
		if (ft_strncmp(&(*str)[start], ((char *)env->content),
			end - start) == 0)
			break ;
		env = env->next;
	}
	if (start == 0)
		start = 1;
	(*str)[start - 1] = '\0';
	if ((*str)[start] == '?' && end == start + 1)
		new_str1 = ft_strjoin(*str, ft_itoa(ex->exit));
	else if (env == NULL)
		new_str1 = ft_strjoin(*str, " \0");
	else
		new_str1 = ft_strjoin(*str, &((char *)env->content)[end - start + 1]);
	new_str2 = ft_strjoin(new_str1, &(*str)[end]);
	free(*str);
	*str = new_str2;
	free(new_str1);
}
