/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:03:36 by artclave          #+#    #+#             */
/*   Updated: 2024/02/11 14:43:29 by artclave         ###   ########.fr       */
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
# include "libft.h"
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
	int		is_builtin_last;
}		t_exec;

//PART 0: MAIN
void	initialize_minishell(t_exec *ex, char **env);
void	execution_main(t_exec *ex);

//PART 1: PREP
void	handle_dollar_sign(t_cmd **cmd_ptr, t_exec *ex);
void	create_pipes(t_cmd *cmd, t_exec *ex);
void	create_child_ids(t_cmd *cmd, t_exec *ex);

//PART 2: EXECUTE
void	process_cmds(t_cmd *cmd, t_exec *ex);
void	execute_command(int id, int curr_cmd, t_cmd *cmd, t_exec *ex);
void	close_open_pipes(int curr_cmd, t_exec *ex);

//PART 2.1: REDIRECTION
void	save_original_io(t_exec *ex);
void	reset_io(t_exec *ex);
void	dup_pipes(int curr_cmd, t_cmd *cmd, t_exec *ex);
void	dup_file_input(t_cmd *cmd);
void	dup_file_output(t_cmd *cmd);
int		are_redirections_valid(t_cmd *cmd);
int		open_file(t_redir *redir, int pipe_fd);

//PART 2:  BUILTIN
int		is_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, t_exec *ex);
//cd
int		exec_cd(char **cmd_array, t_cmd *cmd, t_exec *ex);
//echo
int		exec_echo(char **cmd_array);
//env
int		exec_env(t_exec *ex);
//exit
int		exec_exit(char **cmd_array, t_cmd *cmd);
//export
int		exec_export(char **cmd_array, t_exec *ex);
int		has_unclosed_quotes(char *str, char *cmd);
void	delete_outside_quotes(char **str);
void	add_slash_to_inside_double_quotes(char **str, int len);
void	add_quotes_around_value(char **str);
int		is_variable_start_valid(char *cmd_array, char *original_cmd);
int		is_variable_content_valid(char *cmd_array, char *original_cmd);
void	print_env_alphabetically(t_list *env, t_list *head);
//PWD
int		exec_pwd(t_exec *ex);
//UNSET
int		exec_unset(char **cmd_array, t_exec *ex);

//PART 3: SHLVL
int		is_executable_minishell(char *cmd, t_exec *ex);
int		change_shlvl(int change, t_exec *ex);
void	maybe_increase_shlvl(t_cmd *cmd, t_exec *ex);

//PART 3: POST
void	wait_for_child_exit_status(t_exec *ex);
void	maybe_quit_program(t_exec *ex);

//PART 3: CLEAN
void	clean_list(t_list *list, int clean_content);
void	clean_t_cmd(t_cmd *cmd);
void	add_data_to_cleanup_list(void *content, t_list **list);

//PART 4 : UTILS
void	new_node(void *content, t_list **list);
t_list	*get_last_node(t_list *list);
char	*get_env_value(char *variable, t_list *env_list);
t_list	*get_env_node(char *variable, t_exec *ex);
int		free_data(char *should_exit, char *data, int exit_code);
void	print_error(char *str1, char *str2, char *str3);
int		malloc_error(void);
int		is_digit(char c);
int		is_letter(char c);
void	skip_whitespace(char *str, int *i);
int		str_is_numerical(char *str);
int		has_pipe(t_cmd *cmd);

#endif
