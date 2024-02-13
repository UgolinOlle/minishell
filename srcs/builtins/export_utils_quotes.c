/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:52:30 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:10:05 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin_exec.h"
#include "utils_exec.h"

static void	delete_char_from_str(int delete, char **str);

int	has_unclosed_quotes(char *str, char *cmd)
{
	int		i;
	char	quote;
	int		unclosed_quote;

	i = -1;
	while (str[++i])
	{
		unclosed_quote = TRUE;
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			while (unclosed_quote == TRUE && str[++i])
			{
				if (str[i] == quote)
					unclosed_quote = FALSE;
			}
			if (unclosed_quote == TRUE)
			{
				print_error("export '", cmd, "': not a valid identifier");
				return (free_data(NULL, cmd, 1));
			}
		}
	}
	return (0);
}

void	delete_outside_quotes(char **str)
{
	int		i;
	char	quote;
	int		opening_quote_index;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			quote = (*str)[i];
			opening_quote_index = i;
			while ((*str)[++i])
			{
				if ((*str)[i] == quote)
				{
					delete_char_from_str(opening_quote_index, str);
					delete_char_from_str(--i, str);
					i--;
					break ;
				}
			}
		}
	}
}

static void	delete_char_from_str(int delete, char **str)
{
	int		i;
	int		len;
	char	*new_str;

	len = ft_strlen(*str) - 1;
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return ;
	i = -1;
	ft_strlcpy(new_str, *str, delete + 1);
	ft_strcat(new_str, &(*str)[delete + 1]);
	free(*str);
	*str = new_str;
}

void	add_slash_to_inside_double_quotes(char **str, int len)
{
	int		i;
	int		double_quotes;
	char	*new_str;

	double_quotes = 0;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '"')
			double_quotes++;
	}
	new_str = (char *)malloc(sizeof(char) * len + double_quotes + 1);
	if (!new_str)
		return ;
	double_quotes = 0;
	i = -1;
	while ((*str)[++i])
	{
		new_str[i + double_quotes] = (*str)[i];
		if ((*str)[i] && (*str)[i + 1] == '"')
			new_str[i + ++double_quotes] = '\\';
	}
	new_str[i + double_quotes] = '\0';
	free(*str);
	*str = new_str;
}

void	add_quotes_around_value(char **str)
{
	int		i;
	int		len;
	char	*new_str;

	len = ft_strlen(*str) + 2;
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return ;
	i = -1;
	while ((*str)[++i] && (*str)[i] != '=')
		new_str[i] = (*str)[i];
	if ((*str)[i] != '=')
	{
		free(new_str);
		return ;
	}
	new_str[++i] = '"';
	while (++i < len - 1)
		new_str[i] = (*str)[i - 1];
	new_str[i] = '"';
	new_str[++i] = '\0';
	free(*str);
	*str = new_str;
}
