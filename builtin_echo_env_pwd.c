#include "minishell.h"

int	is_n_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(t_parse_node *parse_node)
{
	int	flag_n;

	flag_n = 0;
	parse_node->option->cur = parse_node->option->head;
	while (parse_node->option->cur != 0
		&& is_n_option(parse_node->option->cur->value) == 0)
	{
		flag_n = 1;
		parse_node->option->cur = parse_node->option->cur->next;
	}
	while (parse_node->option->cur != 0)
	{
		printf("%s ", parse_node->option->cur->value);
		parse_node->option->cur = parse_node->option->cur->next;
	}
	parse_node->arg->cur = parse_node->arg->head;
	while (parse_node->arg->cur != 0)
	{
		printf("%s ", parse_node->arg->cur->value);
		parse_node->arg->cur = parse_node->arg->cur->next;
	}
	printf("\b");
	if (flag_n != 1)
		printf("\n");
	return (0);
}

int	ft_env(t_list *envp_list)
{
	envp_list->cur = envp_list->head;
	while (envp_list->cur != 0)
	{
		if (ft_strncmp(envp_list->cur->key, "?", 2) == 0)
			printf("");
		else
			printf("%s=%s\n", envp_list->cur->key, envp_list->cur->value);
		envp_list->cur = envp_list->cur->next;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	path[1024];

	printf("%s\n", getcwd(path, 1024));
	return (0);
}
