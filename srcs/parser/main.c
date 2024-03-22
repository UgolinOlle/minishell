/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:39:09 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 14:59:17 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief The main function for the paser.
 *
 * @param t_exec *ex - The minishell object.
 * @return void
 */
void	ft_parser(t_exec *ex)
{
	t_lexer	*head;

	head = ex->lexer;
	while (ex->lexer)
	{
		if (ex->lexer->str)
			if (!ft_open_quotes(ex->lexer->str))
				ft_parser_error(ex, ERROR_NO_CLOSE_QUOTE);
		ex->lexer = ex->lexer->next;
	}
	ex->lexer = head;
	ft_add_cmd(&ex->cmd, ex->lexer);
}
