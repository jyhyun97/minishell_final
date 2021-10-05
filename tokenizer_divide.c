/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_divide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:51:30 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/04 21:55:01 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	divide_tokens_helper(char **tokens, int *i, int *j)
{
	if (ft_strncmp(&tokens[*i][*j], "<<", 2) == 0
		|| ft_strncmp(&tokens[*i][*j], ">>", 2) == 0)
		(*j) += 2;
	else if (tokens[*i][*j] == '<'
		|| tokens[*i][*j] == '>' || tokens[*i][*j] == '|')
		(*j)++;
	else
	{
		while (tokens[*i][*j] != '\0' && tokens[*i][*j] != '<'
			&& tokens[*i][*j] != '>' && tokens[*i][*j] != '|')
		{
			if (tokens[*i][*j] == '\'')
				(*j) += skip_quotes(&tokens[*i][*j], '\'');
			else if (tokens[*i][*j] == '"')
				(*j) += skip_quotes(&tokens[*i][*j], '"');
			else
				(*j)++;
		}
	}
}

int	count_tokens(char **tokens)
{
	int	cnt;
	int	i;
	int	j;

	cnt = 0;
	i = 0;
	j = 0;
	while (tokens[i] != 0)
	{
		j = 0;
		while (tokens[i][j] != '\0')
		{
			divide_tokens_helper(tokens, &i, &j);
			cnt++;
		}
		i++;
	}
	return (cnt);
}

char	**divide_tokens(char **tokens)
{
	char	**new_arr;
	int		i;
	int		j;
	int		k;
	int		start;

	new_arr = (char **)malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	i = 0;
	k = 0;
	start = 0;
	while (tokens[i] != 0)
	{
		j = 0;
		while (tokens[i][j] != '\0')
		{
			start = j;
			divide_tokens_helper(tokens, &i, &j);
			new_arr[k] = ft_substr(tokens[i], start, j - start);
			k++;
		}
		i++;
	}
	new_arr[k] = 0;
	arr_free(tokens);
	return (new_arr);
}
