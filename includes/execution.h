/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:03:36 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:21:17 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <gmp.h>
# include <stdio.h>
# include <errno.h>
# include <stdint.h>
# include <limits.h>
# include "minishell.h"
# include "libft.h"

# define SUCCESS 0

# define NO_PIPE -1
# define MAX_PATH_LINUX 4096
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

# define TRUE 1
# define FALSE 0

typedef struct s_exec
{
	t_cmd	*cmd;
	t_list	*env_list;
	int		**fd;
	int		*id;
	int		total_pipes;
	int		total_children;
	int		stdin_original;
	int		stdout_original;
	char	*program_path;
	int		exit;
	t_list	*short_term_data;
	t_list	*long_term_data;
	t_list	*shell_env_list;
	int		is_builtin_last;
}		t_exec;

#endif
