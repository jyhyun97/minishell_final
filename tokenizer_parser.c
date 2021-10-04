#include "minishell.h"

char **arr_free(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	skip_quotes(char const *s, char q)
{
	int	i;

	i = 0;
	if (s[i] == q)
		i++;
	while (s[i] != q && s[i] != '\0')
		i++;
	if (s[i] == q)
		i++;
	return (i);
}

static int	cnt_word(char const *s, char c)
{
	int	i;
	int	cnt;

	if (s == 0)
		return (0);
	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			i += skip_quotes(&s[i], '"');
		else if (s[i] == '\'')
			i += skip_quotes(&s[i], '\'');
		else if (s[i] == '\0')
		{
			cnt++;
			break ;
		}
		else if (s[i] != '\0' && s[i] != '"')
		{
			i++;
		}
		if (s[i] == c || s[i + 1] == '\0')
		{
			while (s[i] == c && s[i] != '\0')
				i++;
			cnt++;
		}
	}
	return (cnt);
}

static int	cnt_letter(char const *s, char c)
{
	int	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			i += skip_quotes(&s[i], '"');
		else if (s[i] == '\'')
			i += skip_quotes(&s[i], '\'');
		else if (s[i] == '\0')
			return (i);
		else if (s[i + 1] == '\0')
		{
			i++;
			return (i);
		}
		else if (s[i] == c)
			return (i);
		else if (s[i] != '\0' && s[i] != '"')
			i++;
	}
	return (i);
}

static char	**arr_fill(char **arr, char const *s, char c)
{
	int	i;
	int	j;

	arr = (char **)malloc(sizeof(char *) * (cnt_word(s, c) + 1));
	if (arr == 0 || s == 0)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			arr[j] = ft_substr(&s[i], 0, cnt_letter(&s[i], c));
			i += cnt_letter(&s[i], c);
			if (arr[j] == 0)
				return (0);
			j++;
			if (s[i] == '\0')
				break ;
		}
		i++;
	}
	arr[j] = 0;
	return (arr);
}

char	**word_split(char const *s, char c)
{
	char	**arr;

	if (s == NULL)
		return (0);
	arr = NULL;
	if ((arr = arr_fill(arr, s, c)) == NULL)
		return (NULL);
	return (arr);
}
