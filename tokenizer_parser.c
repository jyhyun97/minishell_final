/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:55:13 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/09 17:18:57 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arr_fill(char **arr, char const *s, char c)
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
	arr = arr_fill(arr, s, c);
	if (arr == NULL)
		return (NULL);
	return (arr);
}
