#include "minishell.h"

static int	lexicalize_token_helper(char **tokens,
	int *flag_type, t_lex_list *lex_list, int *i)
{
	redirection_without_letter(tokens, &flag_type[TYPE], i);
	if (tokens[*i] == NULL || ft_strncmp(tokens[*i], "<<", 2) == 0
		|| ft_strncmp(tokens[*i], ">>", 2) == 0
		|| tokens[*i][0] == '<' || tokens[*i][0] == '>'
		|| tokens[*i][0] == '|' || tokens[0][0] == '|')
	{
		if (redirection_with_letter(tokens, lex_list, i) == 1)
			return (1);
	}
	else
	{
		if (flag_type[TYPE] == PIPE)
		{
			flag_type[FLAG] = 0;
			(*i)--;
		}
		add_lex_node(lex_list, create_lex_node(flag_type[TYPE], tokens[*i]));
		(*i)++;
	}
	return (0);
}

void	lexicalize_token(char **tokens, t_lex_list *lex_list)
{
	int	i;
	int	flag_type[2];

	i = 0;
	flag_type[FLAG] = 0;
	while (tokens[i] != 0)
	{
		if (ft_strncmp(tokens[i], "<<", 2) == 0
			|| ft_strncmp(tokens[i], ">>", 2) == 0
			|| tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (lexicalize_token_helper(tokens, flag_type, lex_list, &i) == 1)
				break ;
		}
		else if (tokens[i][0] == '|')
		{
			if (lexicalize_pipe(tokens, lex_list, &flag_type[TYPE], &i) == 1)
				return ;
			flag_type[FLAG] = 0;
		}
		else
			lexicalize_other(tokens, lex_list, flag_type, &i);
	}
}
