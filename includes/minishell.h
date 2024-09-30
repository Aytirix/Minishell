/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:00:30 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/23 17:21:41 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define SYNTAX_ERROR "minishell: syntax error near unexpected token"
# define MALLOC "Error: malloc did not work."
# define BOLD_GREEN "\001\033[1;32m\002"
# define BOLD_BLUE "\001\033[1;34m\002"
# define RESET_COLOR "\001\033[0m\002"
# define CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
// EXTENDER

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_env
{
	int				index;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void				env_init(t_env **env, char **envp);
char				**split_for_env(char const *s);
char				**convert_env_tab(t_env *env);
int					env_edit(t_env **lst, t_env *newnode);
int					add_node(t_env **lst, t_env *newnode, int force);
void				add_node_char(char *name, char *value, bool is_free,
						t_env **env);
t_env				*new_node(void *content);
int					max_index(t_env *env);
void				envclear(t_env **lst);
void				print_env(t_env *env);
void				print_export(t_env *env);
t_env				*find_next_index(t_env *env, int index);
void				print_export2(t_env *env);
void				print_brut_format(char c);

// LEXER

typedef enum token
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPENDOUTPUT
}					t_token;

typedef struct s_lexer
{
	char			*content;
	t_token			token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}			t_lexer;

typedef struct s_flag
{
	bool			sg_quote;
	bool			d_quote;
	int				backslash;
}					t_flag;

typedef struct s_index
{
	int				start;
	int				end;
}					t_index;

void				lexer(t_lexer **list, char *str, t_env *env);
char				**ft_split_lexer(char *s);
int					count_words_lexer(char *s);
void				flag_variables_init(t_flag *flag);
int					handle_token(int *res, char *s, bool *flag);
bool				is_token(char c, t_flag f);
int					handle_quotes(char c, t_flag *flag);
void				is_start_of_word(int *res, t_flag f, bool *flag);
void				found_quote(t_index *idx, const char *s);
void				found_word(t_index *idx, const char *s, bool *flag);
void				lexer_init(t_lexer **lexer, char **split, t_env *env);
t_lexer				*new_node_lexer(char *content, t_token tk, int i);
void				add_node_lexer(t_lexer **lst, t_lexer *newnode);
char				*clean_str(char *str, t_env *env);
char				*find_value(char *str, t_env *env);
size_t				handle_dollar(char *clean, char **tab, char *env_value);
size_t				count_dollar(char *str, t_env *env);
void				free_lexer(t_lexer **lexer);
void				print_lexer(t_lexer *lexer);
int					handle_backslash(char c, int *backslash);
t_lexer				*delete_empty_nodes(t_lexer *lexer);
int					strlen2(char *str, t_env *env, bool flag);
void				strlen2_check_dollar(size_t *i, size_t *j, char *str,
						t_env *env);
char				*find_value(char *str, t_env *env);
int					is_special_char(char c);
bool				is_quote(char c, int backslash);
size_t				skip_word(const char *s, char c);

// PARSER

typedef struct s_parser_utils
{
	t_lexer			**lexer;
	t_lexer			*redirections;
	int				nb_of_redirections;
	struct s_parser	**parser;
}					t_parser_utils;

typedef struct s_parser
{
	char			**cmd;
	int				(*builtin)(t_env **, struct s_parser *);
	t_lexer			*redirections;
	int				nb_of_redirections;
	int				pid;
	struct s_parser	*next;
	struct s_parser	*prev;
}					t_parser;

void				parser_init(t_parser **parser, t_lexer **lexer,
						t_parser_utils *utils);
t_lexer				*find_redirection(t_lexer **lexer);
char				**build_command(t_lexer *lexer);
void				detach_from_lexer(t_lexer **lexer);
int					count_pipes(t_lexer *lexer);
int					count_nodes(t_lexer *lexer);
void				print_parser(t_parser *parser);
void				free_parser(t_parser **parser);
void				detach_redirections(t_lexer **lexer, t_parser_utils *utils);

// BUILTINS

void				sigint_handler(int signal);
void				sigint_heredoc_handler(int signal);
void				set_signal_action(void (*handler)(int));
int					my_echo(t_env **env, struct s_parser *parser);
int					my_cd(t_env **env, struct s_parser *parser);
int					my_pwd(t_env **env, struct s_parser *parser);
int					my_export(t_env **env, struct s_parser *parser);
int					my_unset(t_env **env, struct s_parser *parser);
int					remove_env_var(t_env **env, t_env **old, t_env **temp);
int					my_env(t_env **env, struct s_parser *parser);
int					my_exit(t_env **env, struct s_parser *parser);

// EXECUTOR
int					executor(t_env **env, struct s_parser *parser);

#endif