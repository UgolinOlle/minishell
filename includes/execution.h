/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:03:36 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:35:31 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "minishell.h"

# define SUCCESS 0

# define NO_PIPE -1
# define MAX_PATH_LINUX 4096
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

# define TRUE 1
# define FALSE 0

typedef struct s_exec
{
	t_cmd	*cmd; //SHORT
	int		exit; //LONG
	int		**fd; //SHORT
	int		total_pipes;
	int		*id; //SHORT
	t_list	*env_list; //LONG
	t_list	*short_term_data; //SHORT
	t_list	*long_term_data; //LONG
	int		input_error;
	int		quit_program;
}		t_exec; //LONG

void	initialize_minishell(t_exec *ex, char **env);
void	execution(t_exec *ex);
void	create_process_ids(t_cmd *cmd, t_exec *ex);
void	create_pipe_fds(t_cmd *cmd, t_exec *ex);
void	check_redirections_for_curr_cmd(t_cmd *cmd, t_exec *ex);
void	close_all_pipes(int **fd, int total_pipes);
void	dup_input(t_cmd *cmd, int pipe_fd, t_exec *ex);
void	dup_output(t_cmd *cmd, int pipe_fd, t_exec *ex);
int		write_heredoc_to_pipe(char *buffer);
void	execute_command(t_cmd *cmd, t_exec *ex);
void	get_exit_status(t_exec *ex);
void	new_node(void *content, t_list **list);
t_list	*get_last_node(t_list *list);
void	skip_whitespace(char *str, int *i);
int		is_digit(char c);
int		is_letter(char c);
void	exec_cd(t_cmd *cmd, char **cmd_array, t_exec *ex);
void	exec_pwd(void);
void	exec_echo(char **cmd_array);
void	exec_export(char **cmd_array, t_exec *ex);
void	handle_dollar_sign(t_cmd **cmd, t_exec *ex);
void	is_variable_content_valid(char *cmd_array, char *original_cmd);
void	is_variable_start_valid(char *cmd_array, char *original_cmd);
void	print_env_alphabetically(t_list *env, t_list *head);
void	add_slash_to_inside_double_quotes(char **str, int len);
void	add_quotes_around_value(char **str);
void	has_unclosed_quotes(char *str, char *original_cmd);
void	delete_outside_quotes(char **str);
void	exec_unset(char **cmd_array, t_exec *ex);
void	exec_env(t_exec *ex);
void	exec_exit(char **cmd_array, t_redir *redir, t_exec *ex);
void	check_input_error(t_exec *ex);
void	add_data_to_cleanup_list(void *content, t_list **list);
void	clean_list(t_list *list, int clean_content);
void	clean_and_quit_program(t_exec *ex);

#endif
