/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_envp_convert_util.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:27:08 by samin             #+#    #+#             */
/*   Updated: 2021/10/09 13:51:59 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_arr_str_helper1(char *arr_str, char *new_str, int *i, int *j)
{
	while (arr_str[*i] != '$' && arr_str[*i] != '\0')
	{
		new_str[*j] = arr_str[*i];
		(*j)++;
		(*i)++;
	}
}

char	*new_arr_str_helper2(char *arr_str, char *new_str, int *i, int *j)
{
	while (arr_str[*i] != '\0')
	{
		new_str[*j] = arr_str[*i];
		(*j)++;
		(*i)++;
	}
	new_str[*j] = '\0';
	free(arr_str);
	return (new_str);
}

char	*new_arr_str(char *arr_str, char *envp_key, t_list *envp_list)
{
	char	*new_str;
	char	*envp_value;
	int		i;
	int		j;
	int		k;

	envp_value = get_env(envp_key, envp_list);
	new_str = (char *)malloc(sizeof(char)
			* ((int)ft_strlen(arr_str) + (int)ft_strlen(envp_value) + 4));
	i = 0;
	j = 0;
	k = 0;
	new_arr_str_helper1(arr_str, new_str, &i, &j);
	if (arr_str[i] == '$')
	{
		i++;
		while (envp_value[k] != '\0')
		{
			new_str[j] = envp_value[k];
			j++;
			k++;
		}
		i += ft_strlen(envp_key);
	}
	return (new_arr_str_helper2(arr_str, new_str, &i, &j));
}
