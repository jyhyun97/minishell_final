/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 02:10:01 by samin             #+#    #+#             */
/*   Updated: 2021/10/04 12:02:56 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free(char **arr)
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

unsigned int	ft_words_counter(char const *s, char c)
{
	unsigned int	i;
	unsigned int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	if (word == 0)
		return (0);
	return (word);
}

char	**ft_arr_builder(char **arr, char const *s, char c)
{
	unsigned int	i;
	unsigned int	col;
	unsigned int	row;

	i = -1;
	col = 0;
	row = 0;
	arr = (char **)malloc(sizeof(char *) * (ft_words_counter(s, c) + 1));
	if (arr == NULL)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c && s[i] != '\0')
			row++;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			arr[col] = (char *)malloc(sizeof(char) * (row + 1));
			if (arr[col] == NULL)
				return (ft_free(arr));
			row = 0;
			col++;
		}
	}
	arr[col] = NULL;
	return (arr);
}

void	ft_fill(char **arr, char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	col;
	unsigned int	row;

	i = 0;
	j = 0;
	col = 0;
	row = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\0')
		{
			arr[col][row] = s[i];
			j++;
			row++;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			arr[col][row] = '\0';
			col++;
			row = 0;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (s == NULL)
		return (0);
	arr = NULL;
	arr = ft_arr_builder(arr, s, c);
	if (arr == NULL)
		return (NULL);
	ft_fill(arr, s, c);
	return (arr);
}
