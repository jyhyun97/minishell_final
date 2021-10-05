#include "minishell.h"

int	execute_line_helper1(t_parse_list *parse_list,
	t_list *envp_list, t_list *shell_list, int *fd)
{
	int	rtn;

	rtn = 0;
	config_heredoc(parse_list->cur->redirection);
	if (config_redirection(parse_list->cur->redirection) == 1)
	{
		free(envp_list->head->value);
		envp_list->head->value = ft_strdup("1");
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (parse_list->cur->cmd != 0)
	{
		rtn = execute_builtin(parse_list, envp_list, shell_list);
		free(envp_list->head->value);
		envp_list->head->value = ft_itoa(rtn);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

void	execute_line_helper2(t_list *envp_list,
		t_parse_list *parse_list, t_list *shell_list)
{
	int	pid;
	int	status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == 0)
		multi_pipe(parse_list, envp_list, shell_list);
	else
		wait(&status);
	free(envp_list->head->value);
	envp_list->head->value = ft_itoa(status / 256);
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_gloval.new_term));
}

void	execute_line(t_parse_list *parse_list,
		t_list *envp_list, t_list *shell_list)
{
	int	length;
	int	fd[2];

	length = 0;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	parse_list->cur = parse_list->head;
	while (parse_list->cur != 0)
	{
		length++;
		parse_list->cur = parse_list->cur->next;
	}
	parse_list->cur = parse_list->head;
	if (length == 1 && is_builtin(parse_list->cur->cmd) == 0)
	{
		if (execute_line_helper1(parse_list, envp_list, shell_list, fd) == 1)
			return ;
	}
	else
		execute_line_helper2(envp_list, parse_list, shell_list);
}
