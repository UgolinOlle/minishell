/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:35:42 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:02:05 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "prep_exec.h"
#include "process_exec.h"
#include "post_exec.h"
#include "utils_exec.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

t_redir	*get_last_redir_node(t_redir *redir)
{
	while (redir->next)
		redir = redir->next;
	return (redir);
}

t_cmd	*get_last_command_node(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmd	*new_command_node(t_cmd **cmd)
{
	t_cmd	*new_node;
	t_cmd	*prev_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL); //HANDLE ERROR
	memset(new_node, 0, sizeof(t_cmd));
	if (*cmd == NULL)
		*cmd = new_node;
	else
	{
		prev_node = get_last_command_node(*cmd);
		prev_node->next = new_node;
	}
	return (new_node);
}

t_redir	*new_redirect_node(t_cmd **cmd)
{
	t_redir	*new_redir;
	t_redir	*prev_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL); //HANDLE ERROR
	memset(new_redir, 0, sizeof(t_redir));
	if ((*cmd)->redir == NULL)
		(*cmd)->redir = new_redir;
	else
	{
		prev_redir = get_last_redir_node((*cmd)->redir);
		prev_redir->next = new_redir;
	}
	return (new_redir);
}


void	make_command_list(t_exec *ex, char **av, int ac)
{
	t_cmd	*new1;
	t_redir *redir1;
	int		i;

	if (ac == 2)
		(void)redir1;
	ex->cmd = NULL;
	i = 0;
	while (av[++i])
	{
		new1 = new_command_node(&ex->cmd);
		new1->array = ft_split(av[i], ' ');
		if (av[i + 1])
		{
			redir1 = new_redirect_node(&new1);
			redir1->type = PIPE;
			redir1->duplication = STDOUT_FILENO;
		}
		if (i > 1)
		{
			redir1 = new_redirect_node(&new1);
			redir1->type = PIPE;
			redir1->duplication = STDIN_FILENO;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_exec	ex;

	initialize_minishell(&ex, env);
	make_command_list(&ex, av, ac);
	execution_main(&ex);
	return (SUCCESS);
}
