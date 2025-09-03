/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/07/11 19:18:08 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/11 19:18:08 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//--defines--+--library--//
#ifndef MINISHELL_H
# define MINISHELL_H
# define INPUT 1      // "<" .
# define HEREDOC 2    // "<<" .
# define TRUNC 3      // ">" .
# define APPEND 4     // ">>" .
# define PIPE 5       // "|"  .
# define OR_IF 6      // "||" .
# define AND_IF 7     // "&&" .
# define CMD 8        // commande (ex: "ls")
# define ARG 9        // argument (ex: "hello")
# define OPEN_PAR 10  // "("
# define CLOSE_PAR 11 // ")"
# define LIMITER 12
# define REDIR   13
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# include "../libft/libft.h"
# include <stdio.h>
# include "cmd.h"
# include "color.h"
# include "struct.h"
# include "unistd.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

//--//~~variable_globale~~//--//
extern int	g_code_signaux;

//******************builtin******************//

//---------ft_exit---------//
int			ft_exit(t_data *data, char *arg);
int			ft_exit_cmd(t_token *lst, t_data *data);
void		print_error1(void);
void		print_error2(t_data *data, t_token *lst, int i);
void		put_error_without_single_quote(char *str);
int			is_numeric(char *str);
int			is_long_long_range(char *str);
void		free_token_list_exit(t_token *lst);
void		ft_exit_utils(t_exit *s, t_token *lst, t_data *data);
char		*join_exit_argument_if_possible(t_token *lst,
				t_token **next_after, int *token_count);
char		*remove_quotes_and_concatenate(const char *str);
void		ft_verif_exit(char *str, t_data *data);

//---------ft_cd---------//
int			ft_cd(t_token *lst, t_data *data);
int			ft_cd_pipe(char **args, t_data *data);
int			is_empty_var(const char *var_name, char **env);
void		prefix(void);
int			cd_too_many_args(t_token *lst);
int			print_option_issues(char *path);
int			cd_dash_case(t_data *data);
int			cd_home_case(t_data *data);
int			cd_go_home(t_data *data);
int			manage_expanded(t_data *data, char *expanded, char *path);
char		*remove_quotes_cd(char *str);

//---------ft_export---------//
int			ft_export(t_token *lst, t_data *data);
int			ft_export_pipe(char **args, t_data *data);
int			is_event_in_token(char *arg);
int			is_good_token(t_token *lst);
void		replace_tildes(char *str);
void		remove_quotes_from_arg_tab(char **tab);
int			count_args(t_token *lst);
int			find_tiniest_ascii(char **env, int *printed);
void		free_export_variables(t_builtin *s);
int			is_valid_option(char *str);
void		print_export_sorted(char **env);
void		remove_equal(char **env);
int			env_var_exists(char *key, char **envp);
int			is_good_token(t_token *lst);
void		put_error_export(char *str);
int			print_export_error(char *str, int type, char **envp);
int			check_token_validity(t_token *lst);
int			set_ptr_value(t_token *lst, t_builtin *s);
void		set_values_export(t_builtin *s, t_data *data, char *str, int i);
char		**build_args(t_token *lst, t_data *data);
char		*expand_if_needed(char *str, t_data *data);
int			is_valid_key(char *str);

//---------ft_unset---------//
int			ft_unset(t_token *lst, t_data *data);
int			ft_unset_pipe(char **args, t_data *data);
int			handle_unset_error(char *arg);
int			print_unset_error(char *str, int type, char **envp);
int			is_valid_identifier(char *str, t_data *data, int *ptr);
int			print_unset_error(char *str, int type, char **envp);
void		remove_env_var(char *var_name, int dollar, t_data *data);

//---------ft_echo---------//
int			ft_echo(t_token *lst, t_data *data);
int			ft_echo_pipe(char **args, t_data *data);
int			only_ws(char *str);
int			print_between_quote(char *arg,
				int start, char quote_type, t_data *data);
int			is_dollar_in_quote(char *str);
void		echo_token_arg_util(char *arg, int i);
int			is_valid_n_flag(char *arg);
int			check_simple_quote(char *line);
int			putstr_without_quote(char *line);
void		putstr_with_escaping(char *s);
int			handle_dollar_case(char *ptr, t_data *data, int *i);
void		put_expanded(t_builtin *s);
void		put_char_backslash(t_builtin *s, char *arg);

//---------ft_env---------//
int			ft_env(t_token *lst, t_data *data);
int			ft_env_pipe(t_data *data);
int			has_value(char *str);
int			print_env_error(char *arg, int exit_code);
char		*find_line(char *variable, char **envp);
int			variable_size(char *variable);
int			update_pwd(t_data *data);
int			add_env_entry(char ***env_tab, char *new_entry);
char		**build_args_and_advance(t_token **lst, t_data *data);
void		restore_std_fds(int stdin_backup, int stdout_backup);

//---------ft_pwd---------//
int			ft_pwd(t_token *lst);
int			ft_pwd_pipe(t_data *data);

//---------builtin_utils---------//
int			is_builtin(char *arg);
int			exec_builtin_array(char **args, t_data *data, int *backups);
int			exec_builtin(t_token *lst, t_data *data);

//*****************program_utils*****************//

//---------listes---------//
t_token		*ft_lst_token_new(char *arg, int type, int single_quote,
				int colle_next);
void		ft_lstadd_token_back(t_token **lst, t_token *new);
void		ft_print_lst_token(t_token *lst);
int			lstsize(t_token *lst);
void		reorganize_linked_list(t_token *lst);
void		analyze_tokens(t_exec *s);
int			no_args_in_lst(t_token *lst, t_data *data);

//---------env_tab---------//
char		*find_env(char *variable, char **envp);
char		**duplicate_envp(char **envp, char *var);
char		**free_tab(char **tab);
int			check_path(char **envp);
void		add_missing_entry(char ***env_tab);
int			env_var_exists(char *key, char **envp);
char		*get_path(char *cmd, char **envp);
char		*get_env_value(char *key, t_data *data);
int			get_env_index(char **env, char *arg);
int			update_env(char ***env, char *arg);
int			update_shlvl(char ***env_tab, t_data *data);

//---------string_checking---------//
char		*remove_quotes(char *str, t_exec *st);
int			is_only_backslashes(char *str);
int			is_operator_char(char c);
int			is_full_operator(const char *str, int i);
int			is_good_char(char c, int i);
int			check_double_quote(char *line);
int			contains_quote(char *line);

//---------signals---------//
int			singleton(int value);
int			singleton_heredoc(int value);
void		reset_signals_to_default(void);
void		reset_signals_to_sleep(void);
void		init_code_signaux(t_data *data);
void		set_signal_action(void);
void		block_signal(t_data *data);
void		sigint_handler(int signum);

//---------pre_exec_checking---------//
int			is_only_pipe(char *str);
int			is_only_and(char *str);
int			is_only_point_virgule(char *str);
int			is_bad_tokens(t_token *lst);
int			has_unexpected_token(t_exec *s);
int			is_operator_str(char *s);
int			is_a_directory(t_token *lst, t_data *data);
int			is_only_slashes(char *str);
int			ft_is_invalid_input(char *line, t_data *data);
int			is_recursive_path(char *str);
void		fix_cmd_typing(t_token *lst);

//---------error_management---------//
void		print_unexpected(char *token);
int			print_cmd_not_found(char *str);
void		print_invalid_file(char *str);
int			check_quotes_closed(char *line);

//---------file_fd_management---------//
int			which_flags(t_token *lst);
void		close_fds(int fd1, int fd2, int fd3, int to_dup);
int			handle_redirections_cmd(t_token *lst, t_data *data);
void		manage_input(t_exec *s);
void		dup2_and_close_out(int fd);
void		dup2_and_close_in(int fd);
int			create_redirection_file(t_token *lst, t_data *data);
int			manage_bad_fd(t_data *data);
void		close_all_fds(void);

//-----------utils-----------//
void		bzero_line(char *str);
char		*expand_variables(char *line, t_data *data);
int			expand_variables_util(char *line, t_exec *s);
void		making_temp_ptr(char *line, t_exec *s, t_data *data);
char		*ft_strjoin_free(char *s1, char *s2);
int			move_i(int i, char *line, char c);
void		simple_add(t_exec *s, char *line);
void		manage_question_mark2(t_exec *s, t_data *data);
int			add_pid_from_proc(t_exec *s);
int			expand_step(char *line, t_data *data, t_exec *s);
void		manage_quote_and_dollar(t_exec *s, char *line);

//******************parsing******************//

t_token		*ft_tokenize(char *input);
t_token		*ft_parsing(char *input);
int			handle_operator(char *input, int i, t_token **tokens);
int			handle_quote(char *input, int i, t_token **tokens);
int			handle_word(char *input, int i, t_token **tokens);
int			handle_redirection(char *input, int i, t_token **tokens);
int			typetoken(const char *str, int i);
char		*ft_replace_line(char *line);

//********************exec********************//

int			exec(t_token *lst, t_data *data);
void		exec_cmd(char *arg, t_data *data);
int			launch_commands(t_token *lst, t_data *data);
int			pid_result(pid_t *pid_tab, int pid_count);
char		*adding_result(char *ptr, char *to_join, int to_free);
char		*from_char_to_str(char a, char b);
void		set_values(t_exec *s, t_token *lst);
void		init_struct(t_exec *s, t_token *lst);
void		cafd(void);

//******************here_doc*******************//

int			collect_heredocs(t_token *lst, t_data *data);
void		close_heredoc_fds(t_token *lst);
int			checking_heredoc(t_token *lst);
int			get_outfile_fd(t_token *start, t_token *end);
char		*generate_heredoc_filename(void);
int			launch_heredoc_pipes(t_token *lst, t_data *data);
char		**build_args_from_tokens_heredoc(t_token *start,
				t_token *end, t_data *data);
void		handle_redirections_heredoc(t_token *start);
char		*remove_quotes_heredoc(const char *str);
int			exec_cmd_array(char **args, t_data *data, t_exec *st);
void		init_heredoc_fd(t_token *lst);
int			read_one_heredoc(char *limiter, int quoted, t_data *data);
int			adding_value_heredoc(t_exec *s);
void		quit_signal(t_exec *s, t_data *data);
void		ending(t_exec *s);

#endif