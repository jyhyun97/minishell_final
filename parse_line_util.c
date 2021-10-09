/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:22:34 by samin             #+#    #+#             */
/*   Updated: 2021/10/09 17:38:17 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quote(char quote, char *line, int *quote_count, int *i)
{
	(*quote_count)++;
	(*i)++;
	while (line[*i] != '\0' && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
	{
		(*quote_count)++;
		(*i)++;
	}
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
			count_quote('\'', line, &single_quote, &i);
		else if (line[i] == '"')
			count_quote('"', line, &double_quote, &i);
		else if (line[i] != '\0')
			i++;
	}
	if (single_quote % 2 == 0 && double_quote % 2 == 0)
		return (0);
	return (1);
}

int	parse_line_exception(char *line, t_list *envp_list)
{
	if (*line == '\0')
	{
		free(line);
		return (1);
	}
	if (check_even_quote(line) == 1)
	{
		printf("allow only even quote\n");
		free(envp_list->head->value);
		envp_list->head->value = ft_strdup("1");
		free(line);
		return (1);
	}
	return (0);
}
