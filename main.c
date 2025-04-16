
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>




/*void print_tokens(t_token **tokens) {
    printf("Tokens Analysis:\n");
    printf("----------------\n");
    for (int i = 0; tokens[i]; i++) {
        printf("Token %d: [%s]\n", i+1, tokens[i]->token);
        printf("  Type: %s\n", tokens[i]->type);
        printf("----------------\n");
    }
}


int main() {
    char *tests[] = {
        "echo jgjg < mos kgig kgj kg",
        NULL
    };


    printf("=== Input Formatter Test ===\n\n");

    for (int i = 0; tests[i]; i++) {
        printf("Test %d:\n", i + 1);
        printf("Input:  \"%s\"\n", tests[i]);

        char *result = input_formating(tests[i]);
        if (!result) {
            printf("Error: Formatting failed for input\n\n");
            continue;
        }

        printf("Formatted: \"%s\"\n", result);

        t_token **tokens = input_analyse(result);
        if (tokens) {
            print_tokens(tokens);
        }

        free(result);
    }

    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

/*void print_tokens(t_token **tokens) {
    printf("Tokens Analysis:\n");
    printf("----------------\n");
    for (int i = 0; tokens[i]; i++) {
        printf("Token %d: [%s]\n", i+1, tokens[i]->token);
        printf("  Type: %s\n", tokens[i]->type);
        printf("----------------\n");
    }
}

int main(void) {
    char input[1024];

    printf("Enter your command:\n> ");
    if (!fgets(input, sizeof(input), stdin)) {
        perror("Input error");
        return 1;
    }
    char *cleaned = remove_quotes(strdup(input));
    if (!cleaned) {
        printf("Error: Unclosed quote detected!\n");
        return 1;
    }
    char *formatted = input_formating(cleaned);
  
    t_token **tokens = input_analyse(formatted);
    if (tokens) {
        print_tokens(tokens);
    }
    return 0;
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"


char *sanitize_input(char *str)
{
	char *cleaned = remove_quotes(str);
	if (!cleaned) {
		fprintf(stderr, "Error: Unmatched quotes detected.\n");
		return NULL;
	}
	return cleaned;
}

void print_tokens(t_token **tokens) {
    printf("Tokens Analysis:\n");
    printf("----------------\n");
    for (int i = 0; tokens[i]; i++) {
        printf("Token %d: [%s]\n", i+1, tokens[i]->token);
        printf("  Type: %s\n", tokens[i]->type);
        printf("----------------\n");
    }
}

int main(void)
{
	char input[1024];

	printf("Enter command: ");
	if (!fgets(input, sizeof(input), stdin)) {
		perror("Error reading input");
		return 1;
	}
	input[strcspn(input, "\n")] = 0;

	if (!check_quotes(input)) {
		printf("Error: Unmatched quotes detected.\n");
		return 1;
	}

	char **segments = ft_split(input, "|");
	if (!segments)
	{
		fprintf(stderr, "Error splitting input.\n");
		return 1;
	}

	int cmd_id = 1;
	for (int i = 0; segments[i]; i++)
	{
		printf("\n=== Command %d ===\n", cmd_id++);

		char *cleaned = sanitize_input(strdup(segments[i]));
		if (!cleaned) {
			fprintf(stderr, "Sanitization failed.\n");
			continue;
		}

		char *formatted = input_formating(cleaned);
		free(cleaned);

		if (!formatted) {
			fprintf(stderr, "Formatting failed.\n");
			continue;
		}

		printf("Formatted: \"%s\"\n", formatted);

		t_token **tokens = input_analyse(formatted);
		if (tokens) {
			print_tokens(tokens);
		}

		free(formatted);
	}


	return 0;
}
