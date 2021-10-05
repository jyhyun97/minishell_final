/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:58:58 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/05 17:00:09 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_list *envp_list, t_list *shell_list)
{
	t_list	*sorted_list;

	init_list(&sorted_list);
	init_sorted_list(sorted_list, envp_list, shell_list);
	sort_sorted_list(sorted_list);
	print_sorted_list(sorted_list);
	delete_list(&sorted_list);
}

void	export_case_envp(t_parse_node *parse_node,
		t_list *envp_list, t_list *shell_list)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = make_key(parse_node->arg->cur->value);
	tmp_value = make_value(parse_node->arg->cur->value);
	envp_list->cur = envp_list->head;
	while (envp_list->cur != 0)
	{
		if (ft_strcmp(tmp_key, envp_list->cur->key) == 0)
			break ;
		envp_list->cur = envp_list->cur->next;
	}
	free(envp_list->cur->value);
	envp_list->cur->value = tmp_value;
	free(tmp_key);
}

void	export_case_shell(t_parse_node *parse_node,
		t_list *envp_list, t_list *shell_list)
{
	char	*tmp_key;

	tmp_key = make_key(parse_node->arg->cur->value);
	shell_list->cur = shell_list->head;
	while (shell_list->cur != 0)
	{
		if (ft_strcmp(tmp_key, shell_list->cur->key) == 0)
			break ;
		shell_list->cur = shell_list->cur->next;
	}
	delete_node(shell_list);
	free(tmp_key);
	add_node(envp_list, parse_node->arg->cur->value);
}

static void	ft_export2(t_parse_node *parse_node,
	t_list *envp_list, t_list *shell_list)
{
	if (check_export_format(parse_node->arg->cur->value) == 0)
	{
		if (search_list(envp_list,
				parse_node->arg->cur->value) == 0)
			export_case_envp(parse_node, envp_list, shell_list);
		else if (search_list(shell_list,
				parse_node->arg->cur->value) == 0)
			export_case_shell(parse_node, envp_list, shell_list);
		else
			add_node(envp_list, parse_node->arg->cur->value);
	}
	else if (search_list(shell_list,
			parse_node->arg->cur->value) != 0
		&& search_list(envp_list,
			parse_node->arg->cur->value) != 0)
		add_sorted_node(shell_list,
			ft_strdup(parse_node->arg->cur->value), 0);
}

int	ft_export(t_parse_node *parse_node, t_list *envp_list, t_list *shell_list)
{
	int	rtn;

	rtn = 0;
	if (parse_node->arg->head == 0)
		print_export(envp_list, shell_list);
	else
	{
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
				ft_export2(parse_node, envp_list, shell_list);
			parse_node->arg->cur = parse_node->arg->cur->next;
		}
	}
	return (rtn);
}
