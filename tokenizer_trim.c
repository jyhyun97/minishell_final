/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_trim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:39:04 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/04 21:39:32 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	trim_quote_helper1(char *token, char *new_str, int *i, int *j)
{
	(*i)++;
	while (token[*i] != '"')
	{
		new_str[*j] = token[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

void	trim_quote_helper2(char *token, char *new_str, int *i, int *j)
{
	(*i)++;
	while (token[*i] != '\'')
	{
		new_str[*j] = token[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
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
			trim_quote_helper1(token, new_str, &i, &j);
		else if (token[i] == '\'')
			trim_quote_helper2(token, new_str, &i, &j);
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
