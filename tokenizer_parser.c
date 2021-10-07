/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:55:13 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/07 12:55:33 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cnt_word_helper(char const *s, char c, int *i, int *cnt)
{
	if (s[*i] == c || s[*i + 1] == '\0')
	{
		while (s[*i] == c && s[*i] != '\0')
			(*i)++;
		(*cnt)++;
	}
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
			i++;
		cnt_word_helper(s, c, &i, &cnt);
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
	printf("tokenizer_parser 90 %s\n", s);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			arr[j] = ft_substr(&s[i], 0, cnt_letter(&s[i], c));
			printf("tokenizer_parser  96%s\n", arr[j]);
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
	i = 0;
	while (arr[i] != 0)
	{
		printf("tokenizer_parser 110 arr :%s\n", arr[i]);
		i++;
	}
	return (arr);
}

char	**word_split(char const *s, char c)
{
	char	**arr;

	if (s == NULL)
		return (0);
	arr = NULL;
	arr = arr_fill(arr, s, c);
	if (arr == NULL)
		return (NULL);
	int i = 0;
	while (arr[i] != 0)
	{
		printf("tokenizer_parser 129 arr :%s\n", arr[i]);
		i++;
	}
	return (arr);
}
