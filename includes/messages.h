/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:58:38 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/26 14:24:55 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -- COMMON
#define ERROR_MALLOC "minishell: Malloc cannot allocate memory\n"
#define ERROR_NO_ARGS "minishell: no arguments\n"
#define ERROR_NO_CLOSE_QUOTE "minishell: syntax error: unexpected end of file"

// -- LEXER --
#define ERROR_LENGTH_WORD "Error: Word exceeds maximum length\n"

// -- PARSER --
#define ERROR_INVALID_TOKEN "syntax error: invalid token\n"
