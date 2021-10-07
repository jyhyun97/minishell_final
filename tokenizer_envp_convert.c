/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_envp_convert.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:27:00 by samin             #+#    #+#             */
/*   Updated: 2021/10/04 21:27:02 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	measure_env_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*get_env(char *key, t_list *envp_list)
{
	int	i;

	i = 0;
	envp_list->cur = envp_list->head;
	while (envp_list->cur != NULL)
	{
		if (ft_strncmp(envp_list->cur->key, key,
				ft_strlen(envp_list->cur->key)) == 0
			&& ft_strncmp(envp_list->cur->key, key, ft_strlen(key)) == 0)
			return (envp_list->cur->value);
		envp_list->cur = envp_list->cur->next;
	}
	return ("");
}

char	**convert_env(char **arr, t_list *envp_list)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i] != 0)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == '$')
			{
				j++;
				tmp = ft_substr(&arr[i][j], 0, measure_env_key(&arr[i][j]));
				arr[i] = new_arr_str(arr[i], tmp, envp_list);
				free(tmp);
			}
			else if (arr[i][j] == '"')
			{
				j++;
				while (arr[i][j] != '\0' && arr[i][j] != '"')
				{
					if (arr[i][j] == '$')
					{
						j++;
						tmp = ft_substr(&arr[i][j], 0, measure_env_key(&arr[i][j]));
						arr[i] = new_arr_str(arr[i], tmp, envp_list);
						free(tmp);
					}
					j++;
				}
				if (arr[i][j] == '"')
					j++;
			}
			else if (arr[i][j] == '\'')
				j += skip_quotes(&arr[i][j], '\'');
			else
				j++;
		}
		i++;
	}
	return (arr);
}
