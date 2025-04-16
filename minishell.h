#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S_Q '\''
#define D_Q '\"'
#include <stddef.h>
typedef int	t_bool;
// مثال مبسط على هيكل التوكن
typedef struct s_token {
	char	*token;
	char	*type;
}	t_token;

// هيكل خاص بكل أمر مفصول بـ |
typedef struct s_pipe {
	char		*cmd_raw;
	t_token		**tokens;
}	t_pipe;

// الهيكل العام لتحليل سطر الأوامر
typedef struct s_parse {
	char	*line_double_quotes;
	char	*formated_input;
	char	**splt_pipes;
	char   **pipe_parts;
	
}	t_parse;
int check_quotes(const char *input);
char	*remove_quotes(char *str);
char	**ft_split(const char *str, const char *delimiters);
int ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
char *ft_strdup(const char *s);
int count_spc(char *str);
int check_token(char prv, char next);
void f_redirection(char *new_str, const char *old_str, int *i, int *j);
void f_forme_of_q(char *new_str, char *old_str, int *i, int *j);
char *input_formating(char *str);
size_t ft_strlen(const char *s);
t_token **input_analyse(char *str);
void print_tokens(t_token **tokens);
void free_tokens(t_token **tokens);

#endif