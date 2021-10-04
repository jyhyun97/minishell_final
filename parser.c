#include "minishell.h"

void	init_parse_list(t_parse_list **list)
{
	*(list) = (t_parse_list *)malloc(sizeof(t_parse_list));
	(*list)->cur = 0;
	(*list)->head = 0;
	(*list)->tail = 0;
}

void	add_parse_node(t_parse_list *list, t_parse_node *parse_node)
{
	if (list->head == 0 && list->tail == 0)
	{
		list->head = parse_node;
		list->tail = parse_node;
	}
	else
	{
		list->tail->next = parse_node;
		parse_node->prev = list->tail;
		list->tail = parse_node;
	}
}

t_parse_node	*create_parse_node(t_lex_list *lex_list)
{
	t_parse_node	*new_node;

	new_node = malloc(sizeof(t_parse_node));
	ft_bzero(new_node, sizeof(t_parse_node));
	init_lex_list(&new_node->option);
	init_lex_list(&new_node->arg);
	init_lex_list(&new_node->redirection);
	while (lex_list->cur != 0 && lex_list->cur->type != PIPE)
	{
		if (lex_list->cur->type == CMD)
			new_node->cmd = ft_strdup(lex_list->cur->value);
		else if (lex_list->cur->type == OPTION)
			add_lex_node(new_node->option, create_lex_node(lex_list->cur->type, lex_list->cur->value));
		else if (lex_list->cur->type >= 0 && lex_list->cur->type <= 3)
			add_lex_node(new_node->redirection, create_lex_node(lex_list->cur->type, lex_list->cur->value));
		else if (lex_list->cur->type == ARGUMENT)
			add_lex_node(new_node->arg, create_lex_node(lex_list->cur->type, lex_list->cur->value));
		lex_list->cur = lex_list->cur->next;
		if (lex_list->cur == 0)
			break ;
	}
	return (new_node);
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

void	parse_lexer(t_parse_list *parse_list, t_lex_list *lex_list)
{
	int	count;

	count = 0;
	lex_list->cur = lex_list->head;
	while (lex_list->cur != 0)
	{
		add_parse_node(parse_list, create_parse_node(lex_list));
		parse_list->tail->index = count;
		count++;
		if (lex_list->cur != 0)
			lex_list->cur = lex_list->cur->next;
	}
}
