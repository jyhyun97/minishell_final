#include "minishell.h"

int	count_trimed_token(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '"')
		{
			i++;
			while (token[i] != '"')
				i++;
			i++;
		}
		else if (token[i] == '\'')
		{
			i++;
			while (token[i] != '\'')
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

char	*trim_quote(char *token)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(sizeof(char) * (count_trimed_token(token) + 1));
	i = 0;
	j = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '"')
		{
			i++;
			while (token[i] != '"')
			{
				new_str[j] = token[i];
				i++;
				j++;
			}
			i++;
		}
		else if (token[i] == '\'')
		{
			i++;
			while (token[i] != '\'')
			{
				new_str[j] = token[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			new_str[j] = token[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	free(token);
	return (new_str);
}

char	**trim_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		tokens[i] = trim_quote(tokens[i]);
		i++;
	}
	return (tokens);
}
