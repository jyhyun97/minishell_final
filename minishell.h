/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:59:37 by samin             #+#    #+#             */
/*   Updated: 2021/10/05 19:21:11 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
// #include "include/readline/readline.h"
// #include "include/readline/history.h"
# include "libft/libft.h"
# include "struct.h"
# include <termios.h>

# define RD_IN_SINGLE 0  //<
# define RD_OUT_SINGLE 1 // >
# define RD_IN_DOUBLE 2  // <<
# define RD_OUT_DOUBLE 3 // >>
# define PIPE 4
# define CMD 5
# define OPTION 6
# define ARGUMENT 7
# define RD_IN_SINGLE_ERR 100
# define RD_OUT_SINGLE_ERR 101
# define RD_IN_DOUBLE_ERR 102
# define RD_OUT_DOUBLE_ERR 103
# define PIPE_ERR 104
# define NEW_LINE_ERR 105

# define FLAG 0
# define TYPE 1
typedef struct s_gloval
{
	struct termios	org_term;
	struct termios	new_term;
	int				sig_code;
}	t_gloval;

t_gloval	g_gloval;

//builtin_export_util j norm ok
char			*make_key(char *str);
char			*make_value(char *str);
int				search_list(t_list *list, char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				count_node(t_list *list);

//builtin_export j norm ok
void			print_export(t_list *envp_list, t_list *shell_list);
void			export_case_envp(t_parse_node *parse_node,
					t_list *envp_list, t_list *shell_list);
void			export_case_shell(t_parse_node *parse_node,
					t_list *envp_list, t_list *shell_list);
int				ft_export(t_parse_node *parse_node,
					t_list *envp_list, t_list *shell_list);

//builtin_export2 j norm ok
char			check_export_letter(char *str);
int				check_export_format(char *str);
void			delete_node(t_list *list);

//builtin_unset j norm ok
void			delete_key(t_parse_node *parse_node, t_list *list);
int				ft_unset(t_parse_node *parse_node,
					t_list *envp_list, t_list *shell_list);

// builtin_sorted j norm ok
void			add_sorted_node(t_list *list, char *key, char *value);
void			init_sorted_list(t_list *sorted_list,
					t_list *envp_list, t_list *shell_list);
void			sort_sorted_list(t_list *sorted_list);
void			print_sorted_list(t_list *sorted_list);

// builtin cd_exit s norm ok
void			ft_exit_numeric_excption(t_parse_node *parse_node); //추가
void			ft_exit(t_parse_node *parse_node);
void			ft_cd_helper1(t_list *envp_list);
void			ft_cd_helper2(t_list *envp_list);
int				ft_cd(t_lex_node *dir, t_list *envp_list);

// builtin_echo_env_pwd s norm ok
int				is_n_option(char *str);
int				ft_echo(t_parse_node *parse_node);
int				ft_env(t_list *envp_list);
int				ft_pwd(void);

//parse_line_util s norm ok
int				check_even_quote(char *line);
int				parse_line_exception(char *line, t_list *envp_list);
void			tokenizing(char **line, char **trimed_line,
					t_list **envp_list, char ***tokens);
int				lexicalizing(t_lex_list **lex_list,
					char **tokens, t_list *envp_list);
void			parsing(t_parse_list **parse_list, t_lex_list *lex_list);

// execution_line 사민
int				execute_line_helper1(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list, int *fd);
void			execute_line_helper2(t_list *envp_list,
					t_parse_list *parse_list, t_list *shell_list);
void			execute_line(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list);

//execution_multi_pipe 사민
void			multi_pipe_helper4(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list);
void			multi_pipe_helper4(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list);
void			multi_pipe_helper4(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list);
void			multi_pipe_helper4(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list);
void			multi_pipe(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list);

// execution_util 사민
int				count_lex_node(t_lex_list *lex_list);
char			**make_argv(t_parse_node *parse_node, t_list *envp_list);
int				is_builtin(char *cmd);
char			*make_path_helper(char **bins, char *new_path, char *cmd);
char			*make_path(char *cmd, t_list *envp_list);

// execution_util2 사민
void			config_heredoc(t_lex_list *redirection_list);
int				config_redirection(t_lex_list *redirection_list);
void			connect_pipe(int pipefd[2], int io);
int				is_heredoc(t_lex_list *redirection_list);
int				execute_builtin(t_parse_list *parse_list,
					t_list *envp_list, t_list *shell_list);

// lexicalize_util
t_lex_node		*create_lex_node(int type, char *value);
void			init_lex_list(t_lex_list **list);
void			add_lex_node(t_lex_list *list, t_lex_node *lex_node);
void			delete_lex_list(t_lex_list **lex_list);
int				check_syntax_error(t_lex_list *lex_list);

// lexicalize_util2
void			redirection_without_letter(char **tokens, int *type, int *i);
int				redirection_with_letter(char **tokens,
					t_lex_list *lex_list, int *i);
int				lexicalize_pipe(char **tokens,
					t_lex_list *lex_list, int *type, int *i);
void			lexicalize_other(char **tokens, t_lex_list *lex_list,
					int *flag_type, int *i);
// lexicalize_token
void			lexicalize_token(char **tokens, t_lex_list *lex_list);
static int		lexicalize_token_helper(char **tokens,
					int *flag_type, t_lex_list *lex_list, int *i);

// parser j norm ok 
void			init_parse_list(t_parse_list **list);
void			add_parse_node(t_parse_list *list, t_parse_node *parse_node);
t_parse_node	*create_parse_node(t_lex_list *lex_list);
void			delete_parse_list(t_parse_list **parse_list);
void			parse_lexer(t_parse_list *parse_list, t_lex_list *lex_list);

// redirection norm ok
int				redirection_in(char *file);
int				redirection_out(char *file);
int				redirection_double_out(char *file);
void			make_heredoc(char *delimiter);

int				redirection_heredoc(char *delimiter);

// signal j norm ok
void			sig_int(int sig_number);
void			signal_initialize(void);
void			save_input_mode(void);
void			set_input_mode(void);
void			reset_input_mode(void);

//envp_list norm ok
int				split_key_value(char *str, char **key, char **value);
void			envp_list_initialize(char **envp, t_list **envp_list);
void			init_list(t_list **list);
void			add_node(t_list *list, char *str);
void			delete_list(t_list **list);

// tokenizer_divide j norm ok
void			count_tokens_helper(char **tokens, int *i, int *j);
int				count_tokens(char **tokens);
char			**divide_tokens(char **tokens);

// tokenizer_envp_convert s norm ok
int				measure_env_key(char *str);
char			*get_env(char *key, t_list *envp_list);
char			**convert_env(char **arr, t_list *envp_list);

// tokenizer_envp_convert_util s norm ok
void			new_arr_str_helper1(char *arr_str,
					char *new_str, int *i, int *j);
char			*new_arr_str_helper2(char *arr_str,
					char *new_str, int *i, int *j);
char			*new_arr_str(char *arr_str, char *envp_key, t_list *envp_list);

//tokenizer_parser j norm ok
static void		cnt_word_helper(char const *s, char c, int *i, int *cnt);
static int		cnt_word(char const *s, char c);
static int		cnt_letter(char const *s, char c);
static char		**arr_fill(char **arr, char const *s, char c);
char			**word_split(char const *s, char c);

//tokenizer_trim j norm ok
int				count_trimed_token(char *token);
void			trim_quote_helper1(char *token, char *new_str, int *i, int *j);
void			trim_quote_helper2(char *token, char *new_str, int *i, int *j);
char			*trim_quote(char *token);
char			**trim_tokens(char **tokens);

//tokenizer_util j norm ok
char			**arr_free(char **arr);
int				skip_quotes(char const *s, char q);

#endif