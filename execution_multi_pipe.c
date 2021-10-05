#include "minishell.h"

void	multi_pipe_helper1(t_parse_list *parse_list,
	t_list *envp_list, t_list *shell_list)
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
			execve(make_path(parse_list->cur->cmd, envp_list),
				make_argv(parse_list->cur, envp_list), 0);
			printf("%s : command not found\n", parse_list->cur->cmd);
			exit(127);
		}
	}
	exit(0);
}

void	multi_pipe_helper2(t_parse_list *parse_list,
	t_list *envp_list, t_list *shell_list)
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
			execve(make_path(parse_list->cur->cmd, envp_list),
				make_argv(parse_list->cur, envp_list), 0);
			printf("%s : command not found\n", parse_list->cur->cmd);
			exit(127);
		}
	}
	exit(0);
}

void	multi_pipe_helper3(t_parse_list *parse_list,
	t_list *envp_list, t_list *shell_list)
{
	int	status;

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
			execve(make_path(parse_list->cur->cmd, envp_list),
				make_argv(parse_list->cur, envp_list), 0);
			printf("%s : command not found\n", parse_list->cur->cmd);
			exit(127);
		}
	}
	exit(0);
}

void	multi_pipe_helper4(t_parse_list *parse_list,
	t_list *envp_list, t_list *shell_list)
{
	int	status;

	wait(&status);
	if (is_heredoc(parse_list->cur->redirection) == 0)
		connect_pipe(parse_list->cur->pipefd, STDIN_FILENO);
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
			execve(make_path(parse_list->cur->cmd, envp_list),
				make_argv(parse_list->cur, envp_list), 0);
			printf("%s : command not found\n", parse_list->cur->cmd);
			exit(127);
		}
	}
	exit(0);
}

void	multi_pipe(t_parse_list *parse_list,
	t_list *envp_list, t_list *shell_list)
{
	int	pid;
	int	status;

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
			multi_pipe_helper1(parse_list, envp_list, shell_list);
		else
			multi_pipe_helper2(parse_list, envp_list, shell_list);
	}
	else if (parse_list->cur->next != 0)
		multi_pipe_helper3(parse_list, envp_list, shell_list);
	else
		multi_pipe_helper4(parse_list, envp_list, shell_list);
}
