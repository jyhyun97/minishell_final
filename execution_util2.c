/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:31:09 by samin             #+#    #+#             */
/*   Updated: 2021/10/06 12:31:35 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	config_heredoc(t_lex_list *redirection_list)
{
	redirection_list->cur = redirection_list->head;
	while (redirection_list->cur != NULL)
	{
		if (redirection_list->cur->type == RD_IN_DOUBLE)
			make_heredoc(redirection_list->cur->value);
		redirection_list->cur = redirection_list->cur->next;
	}
}

int	config_redirection(t_lex_list *redirection_list)
{
	struct stat	buf;

	redirection_list->cur = redirection_list->head;
	while (redirection_list->cur != NULL)
	{
		if (redirection_list->cur->type == RD_IN_SINGLE)
		{
			if (redirection_in(redirection_list->cur->value) == 1)
				return (1);
		}
		else if (redirection_list->cur->type == RD_OUT_SINGLE)
			redirection_out(redirection_list->cur->value);
		else if (redirection_list->cur->type == RD_IN_DOUBLE)
		{
			if (redirection_heredoc() == 1)
				return (1);
		}
		else if (redirection_list->cur->type == RD_OUT_DOUBLE)
			redirection_double_out(redirection_list->cur->value);
		redirection_list->cur = redirection_list->cur->next;
	}
	if (stat("heredoc_tmp", &buf) == 0)
		unlink("heredoc_tmp");
	return (0);
}

void	connect_pipe(int pipefd[2], int io)
{
	dup2(pipefd[io], io);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	is_heredoc(t_lex_list *redirection_list)
{
	redirection_list->cur = redirection_list->head;
	while (redirection_list->cur != NULL)
	{
		if (redirection_list->cur->type == RD_IN_DOUBLE)
			return (1);
		redirection_list->cur = redirection_list->cur->next;
	}
	return (0);
}

int	execute_builtin(t_parse_list *parse_list,
	t_list *envp_list, t_list *shell_list)
{
	int	rtn;

	rtn = 0;
	if (ft_strncmp(parse_list->cur->cmd, "echo", 5) == 0)
		rtn = ft_echo(parse_list->cur);
	else if (ft_strncmp(parse_list->cur->cmd, "export", 7) == 0)
		rtn = ft_export(parse_list->cur, envp_list, shell_list);
	else if (ft_strncmp(parse_list->cur->cmd, "unset", 6) == 0)
		rtn = ft_unset(parse_list->cur, envp_list, shell_list);
	else if (ft_strncmp(parse_list->cur->cmd, "env", 4) == 0)
		rtn = ft_env(envp_list);
	else if (ft_strncmp(parse_list->cur->cmd, "pwd", 4) == 0)
		rtn = ft_pwd();
	else if (ft_strncmp(parse_list->cur->cmd, "cd", 3) == 0)
		rtn = ft_cd(parse_list->cur->arg->head, envp_list);
	else if (ft_strncmp(parse_list->cur->cmd, "exit", 5) == 0)
		ft_exit(parse_list->cur);
	return (rtn);
}
