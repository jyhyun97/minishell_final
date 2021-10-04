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
			printf("syntax error near unexpected token `%s'\n", lex_list->cur->value);
			return (1);
		}
		lex_list->cur = lex_list->cur->next;
	}
	return (0);
}

void	Lexicalize_token(char **tokens, t_lex_list *lex_list)
{
	int	i;
	int	flag;
	int	type;

	i = 0;
	flag = 0;
	while (tokens[i] != 0)
	{
		if (ft_strncmp(tokens[i], "<<", 2) == 0 || ft_strncmp(tokens[i], ">>", 2) == 0
			|| tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (ft_strncmp(tokens[i], "<<", 2) == 0)
				type = RD_IN_DOUBLE;
			else if (ft_strncmp(tokens[i], ">>", 2) == 0)
				type = RD_OUT_DOUBLE;
			else if (tokens[i][0] == '<')
				type = RD_IN_SINGLE;
			else if (tokens[i][0] == '>')
				type = RD_OUT_SINGLE;
			i++;
			if (tokens[i] == NULL || ft_strncmp(tokens[i], "<<", 2) == 0 || ft_strncmp(tokens[i], ">>", 2) == 0
				|| tokens[i][0] == '<' || tokens[i][0] == '>' || tokens[i][0] == '|' || tokens[0][0] == '|')
			{
				if (tokens[i] == NULL)
				{
					add_lex_node(lex_list, create_lex_node(NEW_LINE_ERR, "error"));
					break ;
				}
				else if (ft_strncmp(tokens[i], "<<", 2) == 0)
					add_lex_node(lex_list, create_lex_node(RD_OUT_DOUBLE_ERR, tokens[i]));
				else if (ft_strncmp(tokens[i], ">>", 2) == 0)
					add_lex_node(lex_list, create_lex_node(RD_IN_DOUBLE_ERR, tokens[i]));
				else if (tokens[i][0] == '<')
					add_lex_node(lex_list, create_lex_node(RD_OUT_SINGLE_ERR, tokens[i]));
				else if (tokens[i][0] == '>')
					add_lex_node(lex_list, create_lex_node(RD_IN_SINGLE_ERR, tokens[i]));
				else if (tokens[i][0] == '|')
					add_lex_node(lex_list, create_lex_node(PIPE_ERR, tokens[i]));
			}
			else
			{
				if (type == PIPE)
				{
					flag = 0;
					i--;
				}
				add_lex_node(lex_list, create_lex_node(type, tokens[i]));
				i++;
			}
		}
		else if (tokens[i][0] == '|')
		{
			type = PIPE;
			i++;
			if (tokens[i] == NULL)
			{
				add_lex_node(lex_list, create_lex_node(PIPE_ERR, "| error")); //문구 수정필요...
				return ;
			}
			else if (tokens[i][0] == '|' || tokens[0][0] == '|')
				add_lex_node(lex_list, create_lex_node(PIPE_ERR, tokens[i]));
			else
				add_lex_node(lex_list, create_lex_node(type, tokens[i]));
			flag = 0;
		}
		else
		{
			if (flag == 0)
			{
				type = CMD;
				flag = 1;
			}
			else if (flag == 1)
			{
				if (tokens[i][0] == '-')
					type = OPTION;
				else
					type = ARGUMENT;
			}
			add_lex_node(lex_list, create_lex_node(type, tokens[i]));
			i++;
		}
	}
}

