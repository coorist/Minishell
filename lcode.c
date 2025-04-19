ct_token *tokenize(const char *input) {
    t_token *tokens = NULL;
    size_t i = 0;

    while (input[i]) {
        // Skip whitespace
        if (input[i] == ' ' || input[i] == '\t') {
            i++;
            continue;
        }

        // Handle pipes
        if (input[i] == '|') {
            add_token(&tokens, new_token(TOK_PIPE, "|"));
            i++;
        }
        // Handle logical AND (&&)
        else if (input[i] == '&' && input[i + 1] == '&') {
            add_token(&tokens, new_token(TOK_AND, "&&"));
            i += 2;
        }
        // Handle logical OR (||)
        else if (input[i] == '|' && input[i + 1] == '|') {
            add_token(&tokens, new_token(TOK_OR, "||"));
            i += 2;
        }
        // Handle redirection in (<)
        else if (input[i] == '<') {
            add_token(&tokens, new_token(TOK_REDIR_IN, "<"));
            i++;
        }
        // Handle redirection out (>)
        else if (input[i] == '>') {
            add_token(&tokens, new_token(TOK_REDIR_OUT, ">"));
            i++;
        }
        // Handle redirection append (>>)
        else if (input[i] == '>' && input[i + 1] == '>') {
            add_token(&tokens, new_token(TOK_REDIR_APPEND, ">>"));
            i += 2;
        }
        // Handle heredoc (<<)
        else if (input[i] == '<' && input[i + 1] == '<') {
            add_token(&tokens, new_token(TOK_REDIR_HEREDOC, "<<"));
            i += 2;
        }
        // Handle parentheses
        else if (input[i] == '(') {
            add_token(&tokens, new_token(TOK_OPEN_PAREN, "("));
            i++;
        }
        else if (input[i] == ')') {
            add_token(&tokens, new_token(TOK_CLOSE_PAREN, ")"));
            i++;
        }
        // Handle word (anything else)
        else {
            size_t start = i;
            while (input[i] && input[i] != ' ' && input[i] != '\t' && input[i] != '|' && input[i] != '&' &&
                   input[i] != '<' && input[i] != '>' && input[i] != '(' && input[i] != ')') {
                i++;
            }
            char *word = strndup(input + start, i - start);
            add_token(&tokens, new_token(TOK_WORD, word));
            free(word);
        }
    }

    // Add EOF token at the end
    add_token(&tokens, new_token(TOK_EOF, ""));
    return tokens;
}
