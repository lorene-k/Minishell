/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:40:31 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/20 14:37:20 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ------------  LIBRARIES  ------------------------------------------------ */
# include "libft.h"
# include "tokens.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* ------------  STRUCTS  -------------------------------------------------- */
extern int			g_sig_id;

typedef enum e_in_out_type
{
	PIPE = 0,
	FILE_REAL = 1,
	NORMAL = 2,
	HEREDOC = 3,
	APPEND = 4,
	TRUNC = 5
}					t_in_out_type;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				fd_out;
	int				fd_in;
	int				args_indexes;
	char			*heredoc;
	t_in_out_type	intype;
	t_in_out_type	outtype;
	char			*path;
	int				builtin;
	int				can_access_file;
	int				cmd_not_found;
	char			*heredoc_file_name;
	int				is_empty;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}					t_cmd;

typedef struct s_infos
{
	int				pipes_nb;
	int				*tube;
	char			**paths;
	t_cmd			**cmd;
	int				cmd_nb;
	int				*pid;
	int				return_code;
	int				g_sig_id_heredoc;
	char			**new_envp;
	char			*input;
	int				printed_error;
	int				sigint_heredoc;
}					t_infos;

/* ------------  FUNCTIONS  ------------------------------------------------ */
/* FREE */
void				free_infos_exit(t_infos *infos);
void				free_infos(t_infos **infos);
void				free_create_commands(t_infos **infos);
void				free_infos_while(t_infos **infos);
void				free_infos_error(t_infos *infos);
void				free_infos_child(t_infos **infos);

/* ENV */
int					env_contains_value_on_table(t_infos *infos, char *key);
void				init_env_var(t_infos *infos, char **envp);
void				set_infos_path(t_infos *infos);
char				*replace_str_var(t_infos *infos, char *str);
int					env_var_exists(t_infos *infos, char *key);
char				*replace_str_var_heredoc(t_infos *infos, char *str);

/* ERRORS */
void				protect_cmd_memory(int i, int z, t_cmd **cmd);
void				print_file_error(t_cmd *cmd, char *file);
void				free_cmd_args(t_cmd *cmd);
void				free_cmd_tokens(char **cmd_array);
void				free_two_tokens(char *actual_token, char *next_token,
						t_cmd *actual_cmd, int arg_id);
void				free_new(t_infos **infos, char *input);

/* PARSING */
void				modify_all_cmd_args(t_infos **infos);
void				delete_redirect_args(t_infos **infos, t_cmd *actual_cmd);
int					check_token_and_assign(t_infos **infos, char *actual_token,
						char *next_token, t_cmd *cmd);
void				remove_one_inout_and_set_inout(t_infos **infos, t_cmd *cmd);
int					get_cmd_id(t_infos *infos, t_cmd *cmd);
void				handle_heredoc(t_cmd *cmd, int i, t_infos *infos,
						int cmd_id);
void				update_infos(t_infos **infos, char *str);
void				create_infos(t_infos **infos, char *str, char **envp);
int					parse(char *str, t_infos **infos, char **envp);
int					exec_command(char **tmp, t_infos *infos);

// CREATE CMDS
t_cmd				*get_cmd(int args_n, char **cmd_array, int last_index,
						t_infos **infos);
int					create_commands(char **cmd_array, t_infos **infos);
void				set_default_cmd_values(t_infos **infos);

// MODIFY CMDS
int					set_infile_outfile(t_infos **infos);

// MODIFY CMDS 2
void				set_in_out_pipes_and_normal(t_infos **infos);
int					set_all_cmd_path(t_infos **infos);

/* SIGNALS */
void				signals_init(void);
void				signals_init_heredoc(void);
void				signals_init_execution(void);

/* EXECUTION */
int					select_builtin(t_infos **infos, int id, int fds[2]);
int					execute_one_builtin(t_infos *infos, int id);
void				close_all_pipe(t_infos *infos);
void				child(t_infos **infos, t_cmd *cmd, int id);
void				create_pipes(t_infos **infos);
void				create_all_fd(t_infos **infos);
void				execute(t_infos **infos);

/* BUILTINS */
int					next_is_empty(t_infos *infos, t_cmd *cmd);
int					update_path(t_infos *infos);
int					check_builtin_error(t_cmd *cmd, char *cmd_name);
int					is_builtin(char *str);
int					ft_pwd(t_infos *infos, t_cmd *cmd);
int					ft_strcmp(char *s1, char *s2);
int					ft_echo(t_infos *infos, t_cmd *cmd);
int					ft_env(t_infos *infos, t_cmd *cmd);
int					ft_export(t_infos *infos, t_cmd *cmd);
int					ft_unset(t_infos *infos, t_cmd *cmd);
int					ft_cd(t_infos *infos, t_cmd *cmd);
int					ft_exit(t_infos *infos, t_cmd *cmd, int *fds);

/* AJOUTS branche env */
int					env_var_exists(t_infos *infos, char *key);
int					add_env_var(t_infos *infos, char *key, char *value);
int					remove_env_var(t_infos *infos, char *key);
char				*get_env_var(t_infos *infos, char *key);
int					contains_env_var(char *str);
int					contains_return_code_var(char *str);

char				*replace_str_var_one_new(t_infos *infos, char *str,
						int heredoc, size_t *cursor);
char				*replace_str_var_new(t_infos *infos, char *str);
char				*replace_one_var_on_str_from_new(t_infos *infos, char *str,
						char *key, size_t i);
char				*replace_str_var_heredoc_new(t_infos *infos, char *str);

/* AJOUTS 8 septembre 17 h 36 */
char				*remove_quotes(char *str);
int					modify_args_cmd(t_cmd *cmd, t_infos *infos);

void				free_create_commands_error(t_infos *infos);
void				free_infos_syntax(t_infos **infos);

// AJOUTS 19 Septembre 13h50
char				*get_var_content(t_infos *infos, char *str);
void				print_sorted_export_env(t_infos *infos);
void				sort_env(char **env);
void				show_one_line_export(char *str);
char				**dup_env(t_infos *infos);
char				*get_var_key(t_infos *infos, char *str, char *var_content);
int					contains_good_characters(char *str);
int					add_var_new(t_infos *infos, char *str);
char				**create_new_args(t_infos **infos, int old_nb_indexes,
						t_cmd *actual_cmd);
int					is_valid_token(char *actual_token);
void				delete_redirect_args(t_infos **infos, t_cmd *actual_cmd);
char				*absolute_path(t_infos **infos, char **all_paths,
						char *cmd);
char				*command_path_parsing(t_infos **infos, char *cmd);

#endif //MINISHELL_H