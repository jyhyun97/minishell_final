/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 01:15:00 by samin             #+#    #+#             */
/*   Updated: 2021/10/04 11:51:42 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*tmp;

	len = ft_strlen(s1) + 1;
	tmp = malloc(len * sizeof(char));
	if (tmp == NULL)
		return (0);
	ft_memcpy(tmp, s1, len);
	return (tmp);
}
