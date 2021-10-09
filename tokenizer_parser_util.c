/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parser_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:55:13 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/09 17:20:37 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_word_helper1(char const *s, char qoute, int *i, int *cnt)
{
	*i += skip_quotes(&s[*i], qoute);
	if (s[*i] == '\0')
	{
		(*cnt)++;
		return (1);
	}
	return (0);
}

void	cnt_word_helper2(char const *s, char c, int *i, int *cnt)
{
	if (s[*i] != '\0' && (s[*i] == c || s[(*i) + 1] == '\0'))
	{
		while (s[*i] == c && s[*i] != '\0')
			(*i)++;
		(*cnt)++;
	}
	if (s[*i] == '\0')
		(*cnt)++;
}

int	cnt_word(char const *s, char c)
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
		{
			if (cnt_word_helper1(s, '"', &i, &cnt) == 1)
				break ;
		}
		else if (s[i] == '\'')
		{
			if (cnt_word_helper1(s, '\'', &i, &cnt) == 1)
				break ;
		}
		else if (s[i] != '\0')
			i++;
		cnt_word_helper2(s, c, &i, &cnt);
	}
	return (cnt);
}

int	cnt_letter(char const *s, char c)
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
