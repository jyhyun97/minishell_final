/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:49:34 by samin             #+#    #+#             */
/*   Updated: 2021/10/04 11:53:46 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)&big[i]);
	while (big[i] != '\0' && len > i)
	{
		if (big[i] == little[0])
		{
			while ((len - i > j) && (big[i + j] == little[j]))
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
