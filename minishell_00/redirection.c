#include "minishell.h"

int	redirection_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("%s : No such file or directory\n", file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirection_out(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirection_double_out(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	make_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

int	redirection_heredoc(char *delimiter)
{
	redirection_in("heredoc_tmp");
	unlink("heredoc_tmp");
	return (0);
}
