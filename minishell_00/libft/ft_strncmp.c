/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:47:42 by samin             #+#    #+#             */
/*   Updated: 2020/10/30 13:09:20 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	i = 0;
	while (n > i)
	{
		if (tmp_s1[i] == '\0' || tmp_s2[i] == '\0' || tmp_s1[i] != tmp_s2[i]) //EXC_BAD_ACCESS (code=1, address=0x0)
			return (tmp_s1[i] - tmp_s2[i]);
		i++;
	}
	return (0);
}
