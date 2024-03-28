/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:16:32 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/28 14:23:43 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print syntax error and relaunch minishell.
 *
 * @param t_exec *ex - The minishell object.
 * @param int token - The token of the error.
 * @param int status - The status of the error.
 * @return void
 */
static void	ft_syntax_error(t_exec *ex, int token, int status)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (token == PIPE)
		ft_putstr_fd("|'\n", STDERR_FILENO);
	else if (token == APPEND)
		ft_putstr_fd(">>'\n", STDERR_FILENO);
	else if (token == OUTFILE)
		ft_putstr_fd(">'\n", STDERR_FILENO);
	else if (token == INFILE)
		ft_putstr_fd("<'\n", STDERR_FILENO);
	else if (token == HEREDOC)
		ft_putstr_fd("<<'\n", STDERR_FILENO);
	ft_parser_clean(ex, status);
}

/**
 * @brief Count number of token in a row except WORD and UNINITIALIZED.
 *
 * @param t_lexer *lexer - The lexer object.
 * @return int - The number of token.
 */
static int	ft_count_tokens(t_lexer *lexer)
{
	int	count;
	int	consecutive_count;

	count = 0;
	consecutive_count = 0;
	while (lexer)
	{
		if (lexer->token != WORD && lexer->token != UNINITIALIZED)
		{
			consecutive_count++;
			if (consecutive_count == 3)
			{
				count++;
				consecutive_count = 0;
			}
		}
		else
			consecutive_count = 0;
		lexer = lexer->next;
	}
	return (count);
}

/**
 * @brief Check if there are double pipes.
 *
 * @param t_lexer *lexer - The lexer object.
 * @param t_exec *ex - The minishell object.
 * @return void
 */
static void	ft_double_pipes(t_lexer *lexer, t_exec *ex)
{
	while (lexer)
	{
		if (lexer->token == PIPE)
		{
			if (lexer->next && (lexer->next->token == PIPE
					|| lexer->next->token == INFILE))
				ft_syntax_error(ex, lexer->next->token, STDERR_FILENO);
			else if (lexer->prev && (lexer->prev->token == APPEND
					|| lexer->prev->token == OUTFILE
					|| lexer->prev->token == INFILE
					|| lexer->prev->token == HEREDOC))
				ft_syntax_error(ex, lexer->prev->token, STDERR_FILENO);
			else if (lexer->next && (lexer->next->token == APPEND
					|| lexer->next->token == INFILE
					|| lexer->next->token == HEREDOC))
				ft_syntax_error(ex, lexer->next->token, STDERR_FILENO);
		}
		lexer = lexer->next;
	}
}

/**
 * @brief Check if there is a file name after a redirection.
 *
 * @param t_lexer *lexer - The lexer object.
 * @param t_exec *ex - The minishell object.
 * @return void
 */
static void	ft_check_redirection(t_lexer *lexer, t_exec *ex)
{
	while (lexer)
	{
		if (lexer->token == APPEND || lexer->token == OUTFILE
			|| lexer->token == INFILE || lexer->token == HEREDOC)
		{
			if (!lexer->next)
				ft_parser_error(ex, 1);
			else if ((lexer->token == APPEND || lexer->token == OUTFILE)
				&& lexer->next->token == INFILE)
				ft_syntax_error(ex, INFILE, STDERR_FILENO);
		}
		lexer = lexer->next;
	}
}

/**
 * @brief Check the syntax of the lexer.
 *
 * @param t_lexer *lexer - The lexer object.
 * @return void
 */
void	ft_check_syntax(t_exec *ex)
{
	t_lexer	*lexer;

	lexer = ex->lexer;
	if (lexer->token == PIPE)
		ft_parser_error(ex, 2);
	while (lexer)
	{
		ft_double_pipes(lexer, ex);
		ft_check_redirection(lexer, ex);
		if (ft_count_tokens(lexer) == 1)
			ft_syntax_error(ex, lexer->next->next->token, STDERR_FILENO);
		lexer = lexer->next;
	}
}
