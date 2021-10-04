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
			redirection_heredoc(redirection_list->cur->value);
		else if (redirection_list->cur->type == RD_OUT_DOUBLE)
			redirection_double_out(redirection_list->cur->value);
		redirection_list->cur = redirection_list->cur->next;
	}
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

void multi_pipe(t_parse_list *parse_list, 
	t_list *envp_list, t_list *shell_list)
{
	int	pid;
	int	i;
	int	status;

	i = 0;
	pid = 0;
	parse_list->cur = parse_list->tail;
	while (parse_list->cur != 0 && pid == 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.org_term));
		pipe(parse_list->cur->pipefd);
		pid = fork();
		if (pid == 0)
			parse_list->cur = parse_list->cur->prev;
	}
	if (parse_list->cur->index == 0)
	{
		if (parse_list->cur->next == 0)
		{
			config_heredoc(parse_list->cur->redirection);
			if (config_redirection(parse_list->cur->redirection) == 1)
				exit(1);
			if (parse_list->cur->cmd != 0)
			{
				if (is_builtin(parse_list->cur->cmd) == 0)
					exit(execute_builtin(parse_list, envp_list, shell_list));
				else
				{
					execve(make_path(parse_list->cur->cmd, envp_list), make_argv(parse_list->cur, envp_list), 0);
					printf("%s : command not found\n", parse_list->cur->cmd);
					exit(127);
				}
			}
			exit(0);
		}
		else
		{
			config_heredoc(parse_list->cur->redirection);
			connect_pipe(parse_list->cur->next->pipefd, STDOUT_FILENO);
			if (config_redirection(parse_list->cur->redirection) == 1)
				exit(1);
			if (parse_list->cur->cmd != 0)
			{
				if (is_builtin(parse_list->cur->cmd) == 0)
					exit(execute_builtin(parse_list, envp_list, shell_list));
				else
				{
					execve(make_path(parse_list->cur->cmd, envp_list), make_argv(parse_list->cur, envp_list), 0);
					printf("%s : command not found\n", parse_list->cur->cmd);
					exit(127);
				}
			}
			exit(0);
		}
	}
	else if (parse_list->cur->next != 0)
	{
		wait(&status);
		if (is_heredoc(parse_list->cur->redirection) == 0)
			connect_pipe(parse_list->cur->pipefd, STDIN_FILENO);
		else
			config_heredoc(parse_list->cur->redirection);
		connect_pipe(parse_list->cur->next->pipefd, STDOUT_FILENO);
		if (config_redirection(parse_list->cur->redirection) == 1)
			exit(1);
		if (parse_list->cur->cmd != 0)
		{
			if (is_builtin(parse_list->cur->cmd) == 0)
				exit(execute_builtin(parse_list, envp_list, shell_list));
			else
			{
				execve(make_path(parse_list->cur->cmd, envp_list), make_argv(parse_list->cur, envp_list), 0);
				printf("%s : command not found\n", parse_list->cur->cmd);
				exit(127);
			}
		}
		exit(0);
	}
	else
	{
		wait(&status);
		if (is_heredoc(parse_list->cur->redirection) == 0)
			connect_pipe(parse_list->cur->pipefd, STDIN_FILENO); //if (rd_list has heredoc)
		else
			config_heredoc(parse_list->cur->redirection);
		if (config_redirection(parse_list->cur->redirection) == 1)
			exit(1);
		if (parse_list->cur->cmd != 0)
		{
			if (is_builtin(parse_list->cur->cmd) == 0)
				exit(execute_builtin(parse_list, envp_list, shell_list));
			else
			{
				execve(make_path(parse_list->cur->cmd, envp_list), make_argv(parse_list->cur, envp_list), 0);
				printf("%s : command not found\n", parse_list->cur->cmd);
				exit(127);
			}
		}
		exit(0);
	}
}

void	execute_line(t_parse_list *parse_list, t_list *envp_list, t_list *shell_list)
{
	int	length;
	int	pid;
	int	status;
	int	fd_in;
	int	fd_out;

	length = 0;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	parse_list->cur = parse_list->head;
	while (parse_list->cur != 0)
	{
		length++;
		parse_list->cur = parse_list->cur->next;
	}
	parse_list->cur = parse_list->head;
	if (length == 1 && is_builtin(parse_list->cur->cmd) == 0)
	{
		config_heredoc(parse_list->cur->redirection);
		if (config_redirection(parse_list->cur->redirection) == 1)
		{
			free(envp_list->head->value);
			envp_list->head->value = ft_strdup("1");
			dup2(fd_in, STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_in);
			close(fd_out);
			return ;
		}
		if (parse_list->cur->cmd != 0)
		{
			int rtn;
			rtn = execute_builtin(parse_list, envp_list, shell_list);
			free(envp_list->head->value);
			envp_list->head->value = ft_itoa(rtn);
		}
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			multi_pipe(parse_list, envp_list, shell_list);
		else
			wait(&status);
		free(envp_list->head->value);
		envp_list->head->value = ft_itoa(status / 256);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.new_term));
	}
}
