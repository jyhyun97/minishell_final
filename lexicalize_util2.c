/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicalize_util2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:03:26 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/06 12:28:02 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_without_letter(char **tokens, int *type, int *i)
{
	if (ft_strncmp(tokens[*i], "<<", 2) == 0)
		*type = RD_IN_DOUBLE;
	else if (ft_strncmp(tokens[*i], ">>", 2) == 0)
		*type = RD_OUT_DOUBLE;
	else if (tokens[*i][0] == '<')
		*type = RD_IN_SINGLE;
	else if (tokens[*i][0] == '>')
		*type = RD_OUT_SINGLE;
	(*i)++;
}

int	redirection_with_letter(char **tokens, t_lex_list *lex_list, int *i)
{
	if (tokens[*i] == NULL)
	{
		add_lex_node(lex_list, create_lex_node(NEW_LINE_ERR, "error"));
		return (1);
	}
	else if (ft_strncmp(tokens[*i], "<<", 2) == 0)
		add_lex_node(lex_list, create_lex_node(RD_OUT_DOUBLE_ERR, tokens[*i]));
	else if (ft_strncmp(tokens[*i], ">>", 2) == 0)
		add_lex_node(lex_list, create_lex_node(RD_IN_DOUBLE_ERR, tokens[*i]));
	else if (tokens[*i][0] == '<')
		add_lex_node(lex_list, create_lex_node(RD_OUT_SINGLE_ERR, tokens[*i]));
	else if (tokens[*i][0] == '>')
		add_lex_node(lex_list, create_lex_node(RD_IN_SINGLE_ERR, tokens[*i]));
	else if (tokens[*i][0] == '|')
		add_lex_node(lex_list, create_lex_node(PIPE_ERR, tokens[*i]));
	return (0);
}

int	lexicalize_pipe(char **tokens, t_lex_list *lex_list, int *type, int *i)
{
	*type = PIPE;
	(*i)++;
	if (tokens[*i] == NULL)
	{
		add_lex_node(lex_list, create_lex_node(PIPE_ERR, "| error"));
		return (1);
	}
	else if (tokens[*i][0] == '|' || tokens[0][0] == '|')
		add_lex_node(lex_list, create_lex_node(PIPE_ERR, tokens[*i]));
	else
		add_lex_node(lex_list, create_lex_node(*type, tokens[*i]));
	return (0);
}

void	lexicalize_other(char **tokens, t_lex_list *lex_list,
	int *flag_type, int *i)
{
	if (flag_type[FLAG] == 0)
	{
		flag_type[TYPE] = CMD;
		flag_type[FLAG] = 1;
	}
	else if (flag_type[FLAG] == 1)
	{
		if (tokens[*i][0] == '-')
			flag_type[TYPE] = OPTION;
		else
			flag_type[TYPE] = ARGUMENT;
	}
	add_lex_node(lex_list, create_lex_node(flag_type[TYPE], tokens[*i]));
	(*i)++;
}

int	count_lex_node(t_lex_list *lex_list)
{
	int	num;

	num = 0;
	lex_list->cur = lex_list->head;
	while (lex_list->cur != 0)
	{
		lex_list->cur = lex_list->cur->next;
		num++;
	}
	return (num);
}
