/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:03:38 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/07 12:24:42 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_list	*parse_line(char *line, t_list *envp_list)
{
	char			**tokens;
	char			*trimed_line;
	t_lex_list		*lex_list;
	t_parse_list	*parse_list;

	if (parse_line_exception(line, envp_list) == 1)
		return (0);
	tokenizing(&line, &trimed_line, &envp_list, &tokens);
	if (lexicalizing(&lex_list, tokens, envp_list) == 1)
		return (0);
	parsing(&parse_list, lex_list);
	return (parse_list);
}

void	minishell_init(char **envp, t_list **envp_list, t_list **shell_list)
{
	save_input_mode();
	set_input_mode();
	signal_initialize();
	envp_list_initialize(envp, envp_list);
	init_list(shell_list);
}

void	minishell_exception(t_list *envp_list, char *line)
{
	if (g_gloval.sig_code != 0)
	{
		free(envp_list->head->value);
		envp_list->head->value = ft_itoa(g_gloval.sig_code);
		g_gloval.sig_code = 0;
	}
	if (line && *line)
		add_history(line);
	else if (line == NULL)
	{
		printf("exit\n");
		reset_input_mode();
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*envp_list;
	t_list			*shell_list;
	t_parse_list	*parse_list;

	if (argc > 1 || argv[0] == 0)
	{
		printf("%s: No such file or directory\n", argv[1]);
		return (0);
	}
	minishell_init(envp, &envp_list, &shell_list);
	while (1)
	{
		line = readline("minishell$ ");
		minishell_exception(envp_list, line);
		parse_list = parse_line(line, envp_list);
		if (parse_list == 0)
			continue ;
		execute_line(parse_list, envp_list, shell_list);
		delete_parse_list(&parse_list);
	}
	reset_input_mode();
	delete_list(&envp_list);
	delete_list(&shell_list);
	return (0);
}
