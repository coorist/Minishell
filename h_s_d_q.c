#include "minishell.h"

char	*clean_until_and_remove(char *str, char target)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != target)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*remove_quotes(char *str)
{
	int		i, j;
	char	quote;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = malloc(strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				new_str[j++] = str[i++];
			if (!str[i]) {
				free(new_str);
				return (NULL);
			}
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

int check_quotes(const char *input) {
    int single = 0, double_q = 0;
    for (int i = 0; input[i]; i++) {
        if (input[i] == S_Q && single % 2 == 0)
            double_q ^= 1;
        else if (input[i] == D_Q && double_q % 2 == 0)
            single ^= 1;
    }
    return (single == 0 && double_q == 0);
}
