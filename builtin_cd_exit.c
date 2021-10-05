/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:06:34 by samin             #+#    #+#             */
/*   Updated: 2021/10/05 18:00:23 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_numeric_excption(t_parse_node *parse_node)
{
	int	i;

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
	if (ft_strlen(parse_node->arg->head->value)
		> ft_strlen("9223372036854775807")
		|| ft_strcmp(parse_node->arg->head->value, "9223372036854775807") > 0)
	{
		printf("exit\nexit: %s: numeric argument required\n",
			   parse_node->arg->head->value);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
		exit(255);
	}
}

void	ft_exit(t_parse_node *parse_node)
{
	int	arg_cout;

	arg_cout = count_lex_node(parse_node->arg);
	if (parse_node->arg->head == 0)
	{
		printf("exit\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
		exit(0);
	}
	if (arg_cout > 1)
	{
		printf("exit\nexit: too many arguments\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
		exit(1);
	}
	ft_exit_numeric_excption(parse_node);
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
	exit(ft_atoi(parse_node->arg->head->value));
}

void	ft_cd_helper1(t_list *envp_list)
{
	envp_list->cur = envp_list->head;
	while (envp_list->cur != 0)
	{
		if (ft_strncmp(envp_list->cur->key, "HOME", 5) == 0)
			return ;
		envp_list->cur = envp_list->cur->next;
	}
}

void	ft_cd_helper2(t_list *envp_list)
{
	char	path[1024];
	char	*old_pwd;

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
		envp_list->cur = envp_list->cur->next;
	}
	envp_list->cur = envp_list->head;
	while (envp_list->cur != 0)
	{
		if (ft_strncmp(envp_list->cur->key, "OLDPWD", 7) == 0)
		{
			free(envp_list->cur->value);
			envp_list->cur->value = old_pwd;
		}
		envp_list->cur = envp_list->cur->next;
	}
}

int	ft_cd(t_lex_node *dir, t_list *envp_list)
{
	if (dir == 0)
	{
		ft_cd_helper1(envp_list);
		if (chdir(envp_list->cur->value) == -1)
		{
			printf("no such file or directory: %s\n", dir->value);
			return (1);
		}
		ft_cd_helper2(envp_list);
	}
	else
	{
		if (chdir(dir->value) == -1)
		{
			printf("no such file or directory: %s\n", dir->value);
			return (1);
		}
		ft_cd_helper2(envp_list);
	}
	return (0);
}
