/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 11:17:30 by samin             #+#    #+#             */
/*   Updated: 2021/10/05 21:54:45 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	redirection_heredoc()
{
	redirection_in("heredoc_tmp");
	return (0);
}
