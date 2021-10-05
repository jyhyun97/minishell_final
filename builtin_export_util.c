/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:54:58 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/05 19:32:31 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_key(char *str)
{
	char	*rst;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	rst = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		rst[i] = str[i];
		i++;
	}
	rst[i] = '\0';
	return (rst);
}

char	*make_value(char *str)
{
	char	*rst;
	int		i;
	int		j;

	i = 0;
	while (str[ft_strlen(str) - i] != '=')
		i++;
	rst = (char *)malloc(sizeof(char) * (i));
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		rst[j] = str[i];
		i++;
		j++;
	}
	rst[j] = '\0';
	return (rst);
}

int	search_list(t_list *list, char *str)
{
	char	*tmp;

	tmp = make_key(str);
	list->cur = list->head;
	while (list->cur != 0)
	{
		if (ft_strncmp(list->cur->key, tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (0);
		}
		list->cur = list->cur->next;
	}
	free(tmp);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	count_node(t_list *list)
{
	int	num;

	num = 0;
	list->cur = list->head;
	while (list->cur != 0)
	{
		num++;
		list->cur = list->cur->next;
	}
	return (num);
}
