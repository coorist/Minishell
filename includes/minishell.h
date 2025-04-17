/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhindou <ykhindou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:46:09 by ykhindou          #+#    #+#             */
/*   Updated: 2025/04/17 16:16:19 by ykhindou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_GROUP
}	t_node_type;

typedef enum e_redirect_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*file;// Delimiter or target file
	char				*heredoc_file;// Path to the tempfile (only for <<)
	int					delimiter_quoted;// 1 if quoted, 0 if not
	struct s_redirect	*next;
}	t_redirect;

typedef enum e_builtin_id
{
	BI_NONE = -1,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}	t_builtin_id;

typedef struct s_command
{
	char			**args;// {"ls", "-l", NULL}
	t_builtin_id	builtin_id;
	t_redirect		*redirects;// linked list of redirections
}	t_command;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	// Used only if type == NODE_COMMAND or NODE_GROUP
	//t_command   	*cmd;   	// for NODE_COMMAND
	union
	{
		t_command		*cmd;// if NODE_COMMAND
		struct s_ast	*group;// if NODE_GROUP
	}	u_content;
}	t_ast;

#endif