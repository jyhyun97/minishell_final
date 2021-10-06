/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:24:28 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/06 12:24:34 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*cur;
	t_node	*tail;
}	t_list;

typedef struct s_lex_node
{
	int					type;
	char				*value;
	struct s_lex_node	*prev;
	struct s_lex_node	*next;
}	t_lex_node;

typedef struct s_lex_list
{
	t_lex_node	*head;
	t_lex_node	*cur;
	t_lex_node	*tail;
}	t_lex_list;

typedef struct s_parse_node
{
	char				*cmd;
	t_lex_list			*option;
	t_lex_list			*arg;
	t_lex_list			*redirection;
	int					pipefd[2];
	int					index;
	struct s_parse_node	*prev;
	struct s_parse_node	*next;
}	t_parse_node;

typedef struct s_parse_list
{
	t_parse_node		*head;
	t_parse_node		*cur;
	t_parse_node		*tail;
}	t_parse_list;

#endif