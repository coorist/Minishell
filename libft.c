#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

size_t ft_strlen(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

size_t ft_strlcpy(char *dst, const char *src, size_t size) {
    size_t i = 0;
    if (size > 0) {
        while (i < size - 1 && src[i]) {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    while (src[i]) i++;
    return i;
}

char *ft_strdup(const char *s) {
    size_t len = ft_strlen(s) + 1;
    char *dup = malloc(len);
    if (dup) ft_strlcpy(dup, s, len);
    return dup;
}
#include <stdlib.h>
#include <stdio.h>

/* يتحقق مما إذا كان الحرف موجودًا ضمن سلسلة الفواصل */
int	is_delimiter(char c, const char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (1);
		delimiters++;
	}
	return (0);
}

/* يعد عدد الكلمات في السلسلة */
static size_t	wordcount(const char *s, const char *delimiters)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && is_delimiter(*s, delimiters))
			s++;
		if (*s && !is_delimiter(*s, delimiters))
		{
			count++;
			while (*s && !is_delimiter(*s, delimiters))
				s++;
		}
	}
	return (count);
}

/* استخراج كلمة واحدة من النص */
static char	*extract_word(const char *str, const char *delimiters)
{
	int		len = 0;
	char	*word;

	while (str[len] && !is_delimiter(str[len], delimiters))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	for (int i = 0; i < len; i++)
		word[i] = str[i];
	word[len] = '\0';
	return (word);
}

/* تحرير الذاكرة عند الفشل */
static void	free_result(char **result, int i)
{
	while (i--)
		free(result[i]);
	free(result);
}

/* ملء النتيجة بالكلمات */
static int	fill_result(char **result, const char *str, const char *delimiters)
{
	int	i = 0;

	while (*str)
	{
		while (*str && is_delimiter(*str, delimiters))
			str++;
		if (*str && !is_delimiter(*str, delimiters))
		{
			result[i] = extract_word(str, delimiters);
			if (!result[i])
			{
				free_result(result, i);
				return (0);
			}
			i++;
			while (*str && !is_delimiter(*str, delimiters))
				str++;
		}
	}
	result[i] = NULL;
	return (1);
}

/* الدالة الرئيسية ft_split */
char	**ft_split(const char *str, const char *delimiters)
{
	char	**result;
	int		word_count;

	if (!str || !delimiters)
		return (NULL);
	word_count = wordcount(str, delimiters);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	if (!fill_result(result, str, delimiters))
		return (NULL);
	return (result);
}