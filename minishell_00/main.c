#include "minishell.h"

void	delete_lex_list(t_lex_list **lex_list)
{
	t_lex_node	*tmp;

	(*lex_list)->cur = (*lex_list)->head;
	while ((*lex_list)->cur != 0)
	{
		free((*lex_list)->cur->value);
		tmp = (*lex_list)->cur->next;
		free((*lex_list)->cur);
		(*lex_list)->cur = tmp;
	}
	free(*lex_list);
	*lex_list = NULL;
}

void	delete_parse_list(t_parse_list **parse_list)
{
	int				i;
	t_parse_node	*tmp;

	i = 0;
	(*parse_list)->cur = (*parse_list)->head;
	while ((*parse_list)->cur != 0)
	{
		i++;
		if ((*parse_list)->cur->cmd != 0)
		{
			free((*parse_list)->cur->cmd);
			(*parse_list)->cur->cmd = NULL;
		}
		if ((*parse_list)->cur->option != 0)
			delete_lex_list(&(*parse_list)->cur->option);
		if ((*parse_list)->cur->arg != 0)
			delete_lex_list(&(*parse_list)->cur->arg);
		if ((*parse_list)->cur->redirection != 0)
			delete_lex_list(&(*parse_list)->cur->redirection);
		tmp = (*parse_list)->cur->next;
		free((*parse_list)->cur);
		((*parse_list)->cur) = NULL;
		(*parse_list)->cur = tmp;
	}
	free(*parse_list);
	(*parse_list) = NULL;
}

int	check_syntax_error(t_lex_list *lex_list)
{
	lex_list->cur = lex_list->head;
	while (lex_list->cur != 0)
	{
		if (lex_list->cur->type >= 100)
		{
			printf("syntax error near unexpected token `%s'\n", lex_list->cur->value);
			return (1);
		}
		lex_list->cur = lex_list->cur->next;
	}
	return (0);
}

int	check_even_quote(char *line)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			single_quote++;
		else if (line[i] == '"')
			double_quote++;
		i++;
	}
	if (single_quote % 2 == 0 && double_quote % 2 == 0)
		return (0);
	return (1);
}

t_parse_list	*parse_line(char *line, t_list *envp_list)
{
	int				i;
	char			**tokens;
	char			*trimed_line;
	t_lex_list		*lex_list;
	t_parse_list	*parse_list;

	i = 0;
	if (line == 0 || *line == '\0')
		return (0);
	if (check_even_quote(line) == 1)
	{
		printf("allow only even quote\n");
		free(envp_list->head->value);
		envp_list->head->value = ft_strdup("1");
		free(line);
		return (0);
	}
	//tokenizing
	trimed_line = ft_strtrim(line, " ");
	free(line);
	tokens = word_split(trimed_line, ' ');
	free(trimed_line);
	tokens = convert_env(tokens, envp_list);
	tokens = divide_tokens(tokens);
	tokens = trim_tokens(tokens);
	//lexicalizing
	init_lex_list(&lex_list);
	Lexicalize_token(tokens, lex_list);
	arr_free(tokens);
	if (check_syntax_error(lex_list) == 1)
	{
		free(envp_list->head->value);
		envp_list->head->value = ft_strdup("258");
		delete_lex_list(&lex_list);
		return (0);
	}
	//parsing
	init_parse_list(&parse_list);
	parse_lexer(parse_list, lex_list);
	delete_lex_list(&lex_list);
	return (parse_list);
}

//gcc *.c -lreadline -lft -L./libft -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*envp_list;
	t_list			*shell_list;
	t_parse_list	*parse_list;

	save_input_mode();
	set_input_mode();
	signal_initialize();
	envp_list_initialize(envp, &envp_list);
	init_list(&shell_list);
	while (1)
	{
		line = readline("minishell$ ");
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
		parse_list = parse_line(line, envp_list);
		if (parse_list == 0)
		{
			continue ;
		}
		execute_line(parse_list, envp_list, shell_list);
		delete_parse_list(&parse_list);
	}
	reset_input_mode();
	delete_list(&envp_list);
	delete_list(&shell_list);
	return (0);
}
