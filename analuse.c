#include "minishell.h"

static int is_command_exists(t_token **tokens)
{
    int i = -1;
    while (tokens[++i])
        if (ft_strcmp(tokens[i]->type, "command") == 0)
            return 1;
    return 0;
}

static void handle_redirection_tokens(t_token *token)
{
    const char *t = token->token;
    if (ft_strcmp(t, "<<") == 0)
        token->type = "her_doc";
    else if (ft_strcmp(t, "<") == 0)
        token->type = "red_input";
    else if (ft_strcmp(t, ">") == 0)
        token->type = "red_out";
    else if (ft_strcmp(t, ">>") == 0)
        token->type = "append";
}

static void handle_contextual_tokens(t_token *token, t_token *prv, int cmd_found)
{
    (void)cmd_found;

    if (!prv)
    {
        token->type = "command";
        return;
    }

    const char *prev_type = prv->type;

    if (ft_strcmp(prev_type, "red_input") == 0) 
        token->type = "infile";
    else if (ft_strcmp(prev_type, "red_out") == 0)
        token->type = "outfile";
    else if (ft_strcmp(prev_type, "append") == 0)
        token->type = "app_outfile";
    else if (ft_strcmp(prev_type, "her_doc") == 0)
        token->type = "limiter"; 
    else if (token->token[0] == '-' && token->token[1] != '\0' &&
             ft_strcmp(prev_type, "command") == 0)
        token->type = "option";
    else if (ft_strcmp(prev_type, "command") == 0 || 
             ft_strcmp(prev_type, "option") == 0 || 
              ft_strcmp(prev_type, "arg") == 0 ||
            ft_strcmp(prev_type, "infile") == 0 ||
             ft_strcmp(prev_type, "outfile") == 0 ||
             ft_strcmp(prev_type, "app_outfile") == 0)
        token->type = "arg";
    else if (ft_strcmp(prev_type, "pipe") == 0)
        token->type = "command";
    else
        token->type = "arg";  // 👈 بدل من "command"
}


void set_tokens_type(t_token *token, t_token *prv, t_token **tokens)
{
    int cmd_found = is_command_exists(tokens);
        if (ft_strcmp(token->token, ">>") == 0 || 
        ft_strcmp(token->token, "<") == 0 ||
        ft_strcmp(token->token, ">") == 0 ||
        ft_strcmp(token->token, "<<") == 0)
    {
        handle_redirection_tokens(token);
    }
    else
    {
        handle_contextual_tokens(token, prv, cmd_found);
    }
}

t_token	*create_new_token(char **line, int i, t_token **tokens, t_token *pre_token)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->token = line[i];
	if (i <= 0)
		pre_token = NULL;
	else
		pre_token = tokens[i - 1];
	set_tokens_type(token, pre_token, tokens);
	return (token);
}

t_token	**input_analyse(char *str)
{
	int		i;
	char	**line;
	t_token	**tokens;

	i = 0;
	line = ft_split(str, " ");
	while (line[i])
		i++;
	tokens = malloc((i + 1) * sizeof(t_token *));

	i = -1;
	while (line[++i])
		tokens[i] = create_new_token(line, i, tokens, NULL);
	tokens[i] = NULL;
	return (tokens);
}

