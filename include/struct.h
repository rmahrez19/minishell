/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:18:31 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:10:19 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "../libft/libft.h"
# include "minishell.h"
# include <sys/types.h>
# include <limits.h>

typedef struct s_token
{
	char				*arg;
	int					type;
	int					heredoc_fd;
	int					double_quote;
	int					colle_next;
	int					to_expand;
	char				*original_string;
	struct s_token		*next;
}						t_token;

typedef struct s_quotes
{
	int		start;
	char	*token_str;
	char	quote;
	int		type_token;
	int		double_q;
	int		colle_next;
}	t_quotes;

typedef struct s_exit
{
	char		*arg;
	int			code;
	int			tok_count;
	t_token		*next;
	t_token		*tmp;
	int			nb;
}	t_exit;

typedef struct s_cd
{
	char	var_name[256];
	int		i;
	int		j;
	char	*env_val;
	char	*result;
	char	full_var[258];
	char	*temp;
	char	*expanded;
	char	cwd[PATH_MAX];
	char	*new_pwd;
	char	*old_pwd;
}	t_cd;

typedef struct s_redir
{
	int		type;
	char	*filename;
}	t_redir;

typedef struct s_data
{
	char				**env_tab;
	int					exit_code;
	int					is_testing;
	int					heredoc_fd;
	int					heredoc_interrupted;
	t_token				*lst;
	int					backups[2];
	int					bad_fd;
	t_token				*start;
}	t_data;

typedef struct s_globalcmd
{
	int		stdin_backup;
	int		stdout_backup;
	int		has_prev_pipe;
	pid_t	pids[1024];
	int		pid_count;
	int		i;
	pid_t	pid;
	int		status;
}	t_globalcmd;

typedef struct s_hdocentry
{
	int					fd;
	char				*limiter;
	int					quoted;
	struct s_hdocentry	*next;
}	t_hdocentry;

typedef struct s_heredoc
{
	int			stdin_backup;
	int			stdout_backup;
	int			heredoc_fd;
	int			fd_out;
	t_token		*start;
	int			is_last;
	t_token		*prev;
	t_hdocentry	*heredoc_list;
	char		*var_start;
	char		*var_end;
	char		*var_name;
	char		*var_value;
	size_t		prefix_len;
	size_t		var_name_len;
	char		*expanded;
	char		*ptr;
}	t_heredoc;

typedef struct s_redirection
{
	int			pipefd[2];
	int			stdin_backup;
	int			stdout_backup;
	pid_t		pids[1024];
	int			pid_index;
	t_token		*start;
	char		**args;
	int			i;
	int			is_last;
	int			status;
	t_token		*end;
}	t_redirection;

typedef struct s_pipe
{
	char	**arguments;
	char	**file_1;
	char	**arg_father;
	char	**arg_child;
	int		fd_1;
	int		fd_2;
	int		fd_in;
	int		fd_out;
	char	*env_path;
	char	**all_paths;
	char	*final_path;
	char	*exec_path;
	char	*path_child;
	char	*path_father;
	int		nullfd;
	int		i;
	int		fd_0;
}	t_pipe;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	t_token	*tmp;
	t_token	*check;
	int		has_heredoc;
	int		has_pipe;
	int		has_redir;
	int		has_cmd;
	int		from_builtin;
	int		and_if;
	int		next_type;
	int		type;
	char	*result;
	char	*var_value;
	char	var_name[256];
	int		i;
	int		j;
	char	full_var[258];
	char	*temp;
	char	buf[2];
	char	**args;
	char	*expanded;
	char	var[256];
	char	*value;
	char	*c;
	char	*special;
	char	*new;
	char	*path;
	int		err_fd;
	pid_t	pid;
	int		pipefd[2];
	int		has_next;
	t_token	*start;
	int		status;
	int		stdin_backup;
	int		stdout_backup;
	int		has_prev_pipe;
	pid_t	pids[1024];
	int		pid_count;
	char	**paths;
	char	*part_path;
	int		fd;
	int		count;
	char	*pid_str;
	char	*count_str;
	char	*filename;
	char	*limiter;
	t_token	*init;
	int		fd_out;
	int		is_last;
	t_token	*prev;
	t_token	*end;
	int		flags;
	int		backups[2];
	int		something_opened;
	char	*line;
	int		quote;
}	t_exec;

typedef struct s_parsing
{
	int		start;
	int		op_len;
	char	*token_str;
	int		type_token;
	char	quote;
	int		colle_next;
	t_token	*new;
	char	*dup;
	t_token	*temp;
	int		fd;
	int		flags;
	char	*tmp;
	char	*expanded;
}	t_parsing;

typedef struct s_builtin
{
	t_token	*temp;
	int		i;
	int		j;
	int		k;
	int		arg_len;
	char	*var_name;
	char	*expanded;
	char	*empty;
	char	*key;
	char	*val;
	char	*tmp;
	char	*joined;
	int		eq_index;
	char	*res;
	int		start;
	char	**split;
	char	*expanded_key;
	char	*new_arg;
	char	**args;
	char	*ptr;
	int		error;
	int		dollar;
	int		*printed;
	int		size;
	int		min;
	int		add_equal;
	int		count;
	int		ft_m;
	int		is_inside;
}	t_builtin;

typedef struct s_utils
{
	int					sign;
	unsigned long long	result;
	char				*ptr;
	int					i;
	int					start;
	int					len;
	char				**env_tab;
	int					j;
	t_token				*temp;
	t_token				*new;
	t_token				*to_free;
	char				*uid_env;
	char				*entry;
	char				path[PATH_MAX];
	char				*res;
	int					is_inside;
}	t_utils;

#endif