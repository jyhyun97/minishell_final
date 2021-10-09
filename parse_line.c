/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:38:22 by samin             #+#    #+#             */
/*   Updated: 2021/10/09 17:38:24 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizing(char **line, char **trimed_line,
			t_list **envp_list, char ***tokens)
{
	*trimed_line = ft_strtrim(*line, " ");
	free(*line);
	*tokens = word_split(*trimed_line, ' ');
	free(*trimed_line);
	*tokens = convert_env(*tokens, *envp_list);
	*tokens = divide_tokens(*tokens);
	*tokens = trim_tokens(*tokens);
}

int	lexicalizing(t_lex_list **lex_list, char **tokens, t_list *envp_list)
{
	init_lex_list(lex_list);
	lexicalize_token(tokens, *lex_list);
	arr_free(tokens);
	if (check_syntax_error(*lex_list) == 1)
	{
		free(envp_list->head->value);
		envp_list->head->value = ft_strdup("258");
		delete_lex_list(lex_list);
		return (1);
	}
	return (0);
}

void	parsing(t_parse_list **parse_list, t_lex_list *lex_list)
{
	init_parse_list(parse_list);
	parse_lexer(*parse_list, lex_list);
	delete_lex_list(&lex_list);
}
