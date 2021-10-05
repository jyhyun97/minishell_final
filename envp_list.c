/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:33:11 by samin             #+#    #+#             */
/*   Updated: 2021/10/05 17:33:48 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_key_value(char *str, char **key, char **value)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '=')
		{
			str[i] = '\0';
			*key = ft_strdup(str);
			if (*key == 0)
				return (0);
			*value = ft_strdup(&str[i + 1]);
			if (*value == 0)
			{
				free(*key);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	envp_list_initialize(char **envp, t_list **envp_list)
{
	int		i;
	char	*env_tmp;

	env_tmp = ft_strdup("?=0");
	init_list(envp_list);
	add_node(*envp_list, env_tmp);
	free(env_tmp);
	i = 0;
	while (envp[i] != 0)
	{
		add_node(*envp_list, envp[i]);
		i++;
	}
	(*envp_list)->cur = (*envp_list)->head;
}

void	init_list(t_list **list)
{
	*(list) = (t_list *)malloc(sizeof(t_list));
	(*list)->cur = 0;
	(*list)->head = 0;
	(*list)->tail = 0;
}

void	add_node(t_list *list, char *str)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	split_key_value(str, &node->key, &node->value);
	node->prev = 0;
	node->next = 0;
	if (list->head == 0 && list->tail == 0)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}
}

void	delete_list(t_list **list)
{
	t_node	*tmp;

	(*list)->cur = (*list)->head;
	while ((*list)->cur != 0)
	{
		tmp = (*list)->cur->next;
		free((*list)->cur);
		(*list)->cur = tmp;
	}
	free(*list);
}
