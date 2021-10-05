#include "minishell.h"

t_lex_node	*create_lex_node(int type, char *value)
{
	t_lex_node	*new_node;

	new_node = malloc(sizeof(t_lex_node));
	new_node->type = type;
	new_node->value = ft_strdup(value);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	init_lex_list(t_lex_list **list)
{
	*(list) = (t_lex_list *)malloc(sizeof(t_lex_list));
	(*list)->cur = 0;
	(*list)->head = 0;
	(*list)->tail = 0;
}

void	add_lex_node(t_lex_list *list, t_lex_node *lex_node)
{
	if (list->head == 0 && list->tail == 0)
	{
		list->head = lex_node;
		list->tail = lex_node;
	}
	else
	{
		list->tail->next = lex_node;
		lex_node->prev = list->tail;
		list->tail = lex_node;
	}
}

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

int	check_syntax_error(t_lex_list *lex_list)
{
	lex_list->cur = lex_list->head;
	while (lex_list->cur != 0)
	{
		if (lex_list->cur->type >= 100)
		{
			printf("syntax error near unexpected token `%s'\n",
				lex_list->cur->value);
			return (1);
		}
		lex_list->cur = lex_list->cur->next;
	}
	return (0);
}
