#include "minishell.h"


int count_spc(char *str) 
{
    int i = 0, count = 0;
    while (str[i]) {
        if ((str[i] == '<' && str[i+1] != '<') || 
            (str[i] == '>' && str[i+1] != '>') || 
            str[i] == '|') count++;
        i++;
    }
    return count;
}

int check_token(char prv, char next) 
{
    if ((prv == '<' && next == '<') || 
        (prv == '>' && next == '>') || 
        (prv == '>' && next != '>') || 
        (prv == '<' && next != '<') || 
        prv == '|') return 1;
    return 0;
}

void f_redirection(char *new_str, const char *old_str, int *i, int *j) 
{
    char c = old_str[*i];
    new_str[(*j)++] = ' ';
    new_str[(*j)++] = c;
    if (old_str[*i] == old_str[*i+1]) {
        new_str[(*j)++] = c;
        (*i)++;
    }
    new_str[(*j)++] = ' ';
}

void f_forme_of_q(char *new_str, char *old_str, int *i, int *j) 
{
    char quote = old_str[*i];
    new_str[(*j)++] = old_str[(*i)++];
    while (old_str[*i] && old_str[*i] != quote)
        new_str[(*j)++] = old_str[(*i)++];
    if (old_str[*i] == quote)
        new_str[(*j)++] = old_str[(*i)++];
}

char *input_formating(char *str) 
{
    int i = -1, j = 0;
    char *formatted = malloc(ft_strlen(str) + count_spc(str)*2 + 1);
    if (!formatted)
        return NULL;
    
    while (str[++i]) {
        if (str[i] == S_Q || str[i] == D_Q) {
            f_forme_of_q(formatted, str, &i, &j);
        } else if (check_token(str[i], str[i+1])) {
            f_redirection(formatted, str, &i, &j);
        } else {
            formatted[j++] = str[i];
        }
    }
    formatted[j] = '\0';
    return formatted;
}

