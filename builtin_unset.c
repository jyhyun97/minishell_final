/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:00:12 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/04 21:27:47 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_key(t_parse_node *parse_node, t_list *list)
{
	char	*tmp_key;

	tmp_key = make_key(parse_node->arg->cur->value);
	list->cur = list->head;
	while (list->cur != 0)
	{
		if (ft_strcmp(tmp_key, list->cur->key) == 0)
			break ;
		list->cur = list->cur->next;
	}
	delete_node(list);
	free(tmp_key);
}

int	ft_unset(t_parse_node *parse_node, t_list *envp_list, t_list *shell_list)
{
	int		rtn;

	rtn = 0;
	parse_node->arg->cur = parse_node->arg->head;
	while (parse_node->arg->cur != 0)
	{
		if (check_export_letter(parse_node->arg->cur->value) != 0)
		{
			printf("export: `%s': not a valid identifier\n",
				parse_node->arg->cur->value);
			rtn = 1;
		}
		else
		{
			if (search_list(envp_list, parse_node->arg->cur->value) == 0)
				delete_key(parse_node, envp_list);
			else if (search_list(shell_list, parse_node->arg->cur->value) == 0)
				delete_key(parse_node, shell_list);
		}
		parse_node->arg->cur = parse_node->arg->cur->next;
	}
	return (rtn);
}
