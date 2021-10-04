/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:40:08 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/04 21:40:14 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arr_free(char **arr)
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
