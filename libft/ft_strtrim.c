/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:50:46 by samin             #+#    #+#             */
/*   Updated: 2021/10/04 11:54:00 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cutprefix(const char *str, const char *set, size_t s1len)
{
	size_t	i;

	i = 0;
	while (i < s1len)
	{
		if (!(ft_strchr(set, str[i])))
			break ;
		i++;
	}
	return (i);
}

int	cutsuffix(const char *str, const char *set, size_t s1len)
{
	size_t	i;

	i = 0;
	while (i < s1len)
	{
		if (!(ft_strchr(set, str[s1len - i - 1])))
			break ;
		i++;
	}
	return (s1len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s1len;
	int		cut_prefix;
	int		cut_surfix;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	s1len = ft_strlen(s1);
	cut_prefix = cutprefix(s1, set, s1len);
	cut_surfix = cutsuffix(s1, set, s1len);
	if (cut_prefix >= cut_surfix)
		return (ft_strdup(""));
	str = (char *)malloc((cut_surfix - cut_prefix + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + cut_prefix, cut_surfix - cut_prefix + 1);
	return (str);
}
