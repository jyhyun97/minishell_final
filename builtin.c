#include "minishell.h"

int ft_echo(t_parse_node *parse_node)
{
	int flag_n;

	flag_n = 0;
	parse_node->option->cur = parse_node->option->head;
	while (parse_node->option->cur != 0 && is_n_option(parse_node->option->cur->value) == 0)
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

void ft_exit_numeric_excption(t_parse_node *parse_node)
{
	int i;

	i = -1;
	while (++i < ft_strlen(parse_node->arg->head->value))
	{
		if (ft_isdigit(parse_node->arg->head->value[i]) == 0)
		{
			printf("exit\nexit: %s: numeric argument required\n",
				   parse_node->arg->head->value);
			tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
			exit(255);
		}
	}
	if (ft_strlen(parse_node->arg->head->value) > ft_strlen("9223372036854775807") || ft_strcmp(parse_node->arg->head->value, "9223372036854775807") > 0)
	{
		printf("exit\nexit: %s: numeric argument required\n",
			   parse_node->arg->head->value);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
		exit(255);
	}
}

void ft_exit(t_parse_node *parse_node)
{
	int arg_cout;

	arg_cout = count_lex_node(parse_node->arg);
	if (arg_cout > 1)
	{
		printf("exit\nexit: too many arguments\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
		exit(1);
	}
	ft_exit_init(parse_node);
	if (parse_node->arg->head == 0)
	{
		printf("exit\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
		exit(0);
	}
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
	exit(ft_atoi(parse_node->arg->head->value));
}

int ft_env(t_list *envp_list)
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

int ft_pwd(void)
{
	char path[1024];

	printf("%s\n", getcwd(path, 1024));
	return (0);
}

// void ft_cd_1(t_lex_node *dir, t_list *envp_list)
// {
// 	char	path[1024];
// 	char	*old_pwd;

// 	envp_list->cur = envp_list->head;
// 	while (envp_list->cur != 0)
// 	{
// 		if (ft_strncmp(envp_list->cur->key, "PWD", 4) == 0)
// 		{
// 			old_pwd = ft_strdup(envp_list->cur->value);
// 			free(envp_list->cur->value);
// 			envp_list->cur->value = NULL;
// 			envp_list->cur->value = ft_strdup(getcwd(path, 1024));
// 		}
// 		if (ft_strncmp(envp_list->cur->key, "OLDPWD", 7) == 0)
// 		{
// 			free(envp_list->cur->value);
// 			envp_list->cur->value = old_pwd;
// 			return (0);
// 		}
// 		envp_list->cur = envp_list->cur->next;
// 	}
// }

int ft_cd(t_lex_node *dir, t_list *envp_list)
{
	int		nResult;
	char	path[1024];
	char	*old_pwd;

	if (dir == 0)
	{
		envp_list->cur = envp_list->head;
		while (envp_list->cur != 0)
		{
			if (ft_strncmp(envp_list->cur->key, "HOME", 5) == 0)
				break ;
			envp_list->cur = envp_list->cur->next;
		}
		nResult = chdir(envp_list->cur->value);
		if (nResult == -1)
		{
			printf("no such file or directory: %s\n", dir->value);
			return (1);
		}
		envp_list->cur = envp_list->head;
		while (envp_list->cur != 0)
		{
			if (ft_strncmp(envp_list->cur->key, "PWD", 4) == 0)
			{
				old_pwd = ft_strdup(envp_list->cur->value);
				free(envp_list->cur->value);
				envp_list->cur->value = NULL;
				envp_list->cur->value = ft_strdup(getcwd(path, 1024));
			}
			if (ft_strncmp(envp_list->cur->key, "OLDPWD", 7) == 0)
			{
				free(envp_list->cur->value);
				envp_list->cur->value = old_pwd;
				return (0);
			}
			envp_list->cur = envp_list->cur->next;
		}
	}
	else
	{
		nResult = chdir(dir->value);
		if (nResult == -1)
		{
			printf("no such file or directory: %s\n", dir->value);
			return (1);
		}
		envp_list->cur = envp_list->head;
		while (envp_list->cur != 0)
		{
			if (ft_strncmp(envp_list->cur->key, "PWD", 4) == 0)
			{
				old_pwd = ft_strdup(envp_list->cur->value);
				free(envp_list->cur->value);
				envp_list->cur->value = NULL;
				envp_list->cur->value = ft_strdup(getcwd(path, 1024));
			}
			if (ft_strncmp(envp_list->cur->key, "OLDPWD", 7) == 0)
			{
				free(envp_list->cur->value);
				envp_list->cur->value = old_pwd;
				return (0);
			}
			envp_list->cur = envp_list->cur->next;
		}
	}
	return (0);
}
