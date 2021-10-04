/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_sorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:01:35 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/04 17:01:48 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_sorted_node(t_list *list, char *key, char *value)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	ft_bzero(node, sizeof(t_node));
	if (key != 0)
		node->key = key;
	if (value != 0)
		node->value = value;
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

void	init_sorted_list(t_list *sorted_list,
	t_list *envp_list, t_list *shell_list)
{
	envp_list->cur = envp_list->head;
	while (envp_list->cur != 0)
	{
		add_sorted_node(sorted_list, envp_list->cur->key,
			envp_list->cur->value);
		envp_list->cur = envp_list->cur->next;
	}
	shell_list->cur = shell_list->head;
	while (shell_list->cur != 0)
	{
		add_sorted_node(sorted_list, shell_list->cur->key,
			shell_list->cur->value);
		shell_list->cur = shell_list->cur->next;
	}
}

void	sort_sorted_list(t_list *sorted_list)
{
	t_node	tmp;
	int		cnt;
	int		i;

	cnt = count_node(sorted_list);
	i = 0;
	while (i < cnt)
	{
		sorted_list->cur = sorted_list->head;
		while (sorted_list->cur->next != 0)
		{
			if (ft_strcmp(sorted_list->cur->key,
					sorted_list->cur->next->key) > 0)
			{
				tmp.key = sorted_list->cur->key;
				tmp.value = sorted_list->cur->value;
				sorted_list->cur->key = sorted_list->cur->next->key;
				sorted_list->cur->value = sorted_list->cur->next->value;
				sorted_list->cur->next->key = tmp.key;
				sorted_list->cur->next->value = tmp.value;
			}
			sorted_list->cur = sorted_list->cur->next;
		}
		i++;
	}
}

void	print_sorted_list(t_list *sorted_list)
{
	sorted_list->cur = sorted_list->head;
	while (sorted_list->cur != 0)
	{
		if ((ft_strncmp(sorted_list->cur->key, "?", 2)) == 0)
			printf("");
		else if (sorted_list->cur->value == 0
			|| *sorted_list->cur->value == '\0')
			printf("declare -x %s\n", sorted_list->cur->key);
		else
			printf("declare -x %s=\"%s\"\n",
				sorted_list->cur->key, sorted_list->cur->value);
		sorted_list->cur = sorted_list->cur->next;
	}
}
