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

char	check_export_letter(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?' || str[i] == '=' || str[i] == '$' || str[i] == '.')
		return (str[i]);
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '?' || str[i] == '$' || str[i] == '.')
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
				printf("export: `%s': not a valid identifier\n", parse_node->arg->cur->value);
				rtn = 1;
			}
			else
			{
				if (check_export_format(parse_node->arg->cur->value) == 0)
				{
					if (search_list(envp_list, parse_node->arg->cur->value) == 0)
						export_case_envp(parse_node, envp_list, shell_list);
					else if (search_list(shell_list, parse_node->arg->cur->value) == 0)
						export_case_shell(parse_node, envp_list, shell_list);
					else
						add_node(envp_list, parse_node->arg->cur->value);
				}
				else if (search_list(shell_list, parse_node->arg->cur->value) != 0 && search_list(envp_list, parse_node->arg->cur->value) != 0)
					add_sorted_node(shell_list, ft_strdup(parse_node->arg->cur->value), 0);
			}
			parse_node->arg->cur = parse_node->arg->cur->next;
		}
	}
	return (rtn);
}

int	ft_unset(t_parse_node *parse_node, t_list *envp_list, t_list *shell_list)
{
	int	rtn;

	rtn = 0;
	parse_node->arg->cur = parse_node->arg->head;
	while (parse_node->arg->cur != 0)
	{
		if (check_export_letter(parse_node->arg->cur->value) != 0)
		{
			printf("export: `%s': not a valid identifier\n", parse_node->arg->cur->value);
			rtn = 1;
		}
		else
		{
			if (search_list(envp_list, parse_node->arg->cur->value) == 0)
			{
				char *tmp_key;
				tmp_key = make_key(parse_node->arg->cur->value);
				envp_list->cur = envp_list->head;
				while (envp_list->cur != 0)
				{
					if (ft_strcmp(tmp_key, envp_list->cur->key) == 0)
						break ;
					envp_list->cur = envp_list->cur->next;
				}
				delete_node(envp_list);
				free(tmp_key);
			}
			else if (search_list(shell_list, parse_node->arg->cur->value) == 0)
			{
				char *tmp_key;
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
			}
		}
		parse_node->arg->cur = parse_node->arg->cur->next;
	}
	return (rtn);
}