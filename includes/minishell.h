/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:06:13 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 06:31:21 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE 0
# define OUTFILE 1
# define APPEND 2
# define INFILE 3
# define HEREDOC 4

typedef struct s_redir
{
	int				type;
	char			*file_name;
	char			*heredoc_buff;
	int				duplication;
	struct s_redir	*next;
}		t_redir;

typedef struct s_cmd
{
	char			**array;
	t_redir			*redir;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

#endif
