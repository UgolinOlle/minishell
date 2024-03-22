/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:55:23 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 15:01:00 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize the command and redirection structure.
 *
 * @param t_exec *ex - The minishell object.
 * @return void
 */
t_cmd	*ft_init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->array = NULL;
	new_cmd->redir = NULL;
	new_cmd->bad_substitution = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

/**
 * @brief Initialize the redirection structure.
 *
 * @param t_cmd **node, pointer to node which teh redireciton belongs to
 * @return t_redir* The new redirection.
 */
t_redir	*ft_init_redir(t_cmd **node)
{
	t_redir	*new_redir;
	t_redir	*last;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->file_name = NULL;
	new_redir->heredoc_buff = NULL;
	new_redir->type = UNINITIALIZED;
	new_redir->duplication = UNINITIALIZED;
	new_redir->next = NULL;
	if ((*node)->redir == NULL)
		(*node)->redir = new_redir;
	else
	{
		last = (*node)->redir;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
	return (new_redir);
}

/**
 * @brief fills data for redirection node
 *
 * @param t_cmd **node, pointer to current command node
 * @param t_lexer *lexer, pointer to lexer node containing redireciton token
 * @return void
 */
void	ft_add_redir(t_cmd **node, t_lexer **lexer)
{
	t_redir	*redir;

	redir = ft_init_redir(node);
	redir->type = (*lexer)->token;
	if (redir->type == OUTFILE)
		redir->duplication = STDOUT_FILENO;
	if (redir->type == PIPE)
	{
		if ((*node)->array)
			redir->duplication = STDOUT_FILENO;
		return ;
	}
	*lexer = (*lexer)->next;
	if (*lexer && (int)(*lexer)->token == redir->type)
	{
		redir->type = HEREDOC;
		if ((*lexer)->token == OUTFILE)
			redir->type = APPEND;
		*lexer = (*lexer)->next;
	}
	if (redir->type != HEREDOC)
		redir->file_name = (*lexer)->str;
}

/**
 * @brief fills data for one command node.
 *
 * @param t_cmd **cmd, pointer to command structure
 * @param t_lexer *lexer, pointer to first lexer node for each "command node"
 * @return void
 */
int	ft_add_cmd(t_cmd **cmd, t_lexer *lexer)
{
	t_cmd	*node;
	int		i;

	node = ft_init_cmd();
	if (!node)
		return (0);
	node->bad_substitution = 0;
	node->redir = NULL;
	node->next = NULL;
	node->array = ft_malloc_node_array(lexer);
	i = -1;
	while (lexer)
	{
		if (lexer->str && lexer->token == WORD)
			node->array[++i] = ft_strdup(lexer->str);
		if (lexer->token != WORD)
			ft_add_redir(&node, &lexer);
		if (lexer->token == PIPE)
		{
			if (node->array && node->array[0])
				break ;
		}
		lexer = lexer->next;
	}
	node->array[++i] = NULL;
	ft_add_cmd_node_to_list(node, cmd);
	if (lexer && lexer->token == PIPE)
	{
		lexer = lexer->next;
		ft_add_cmd(cmd, lexer);
	}
	return (1);
}
