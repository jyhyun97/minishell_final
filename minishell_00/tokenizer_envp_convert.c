#include "minishell.h"

int measure_env_key(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '"' || str[i] == '\'' || str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			break;
		}
		i++;
	}
	return (i);
}

char	*get_env(char *key, t_list *envp_list)
{
	int	i;

	i = 0;
	envp_list->cur = envp_list->head;
	while (envp_list->cur != NULL)
	{
		if (ft_strncmp(envp_list->cur->key, key, ft_strlen(envp_list->cur->key)) == 0
			&& ft_strncmp(envp_list->cur->key, key, ft_strlen(key)) == 0)
			return (envp_list->cur->value);
		envp_list->cur = envp_list->cur->next;
	}
	return ("");
}

char	*new_arr_str(char *arr_str, char *envp_key, t_list *envp_list)
{
	char	*new_str;
	char	*envp_value;
	int		i;
	int		j;
	int		k;

	envp_value = get_env(envp_key, envp_list);
	new_str = (char *)malloc(sizeof(char) * ((int)ft_strlen(arr_str) + (int)ft_strlen(envp_value) + 4));
	i = 0;
	j = 0;
	k = 0;
	while (arr_str[i] != '$' && arr_str[i] != '\0')
	{
		new_str[j] = arr_str[i];
		j++;
		i++;
	}
	if (arr_str[i] == '$')
	{
		i++;
		while (envp_value[k] != '\0')
		{
			new_str[j] = envp_value[k];
			j++;
			k++;
		}
		i += ft_strlen(envp_key);
	}
	while (arr_str[i] != '\0')
	{
		new_str[j] = arr_str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	free(arr_str);
	return (new_str);
}

char	**convert_env(char **arr, t_list *envp_list)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (arr[i] != 0)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == '$')
			{
				j++;
				tmp = ft_substr(&arr[i][j], 0, measure_env_key(&arr[i][j]));
				arr[i] = new_arr_str(arr[i], tmp, envp_list);
				free(tmp);
			}
			else if (arr[i][j] == '\'')
				j += skip_quotes(&arr[i][j], '\'');
			else
				j++;
		}
		i++;
	}
	return (arr);
}
