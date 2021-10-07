/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:00:56 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/06 11:58:34 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_export_letter(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0)
		return (str[i]);
	i++;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '=')
			return (str[i]);
		i++;
	}
	return (0);
}

int	check_export_format(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (1);
	i++;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (1);
	i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	delete_node(t_list *list)
{
	if (list->cur == list->head && list->cur == list->tail)
	{
		free(list->cur);
		ft_bzero(list, sizeof(t_list));
		return ;
	}
	else if (list->cur == list->head)
	{
		list->head = list->cur->next;
		list->head->prev = 0;
	}
	else if (list->cur == list->tail)
	{
		list->tail = list->cur->prev;
		list->tail->next = 0;
	}
	else
	{
		list->cur->prev->next = list->cur->next;
		list->cur->next->prev = list->cur->prev;
	}
	free(list->cur->key);
	free(list->cur->value);
	free(list->cur);
}
