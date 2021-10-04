/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:03:56 by samin             #+#    #+#             */
/*   Updated: 2020/11/09 17:02:09 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *a, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp_a;

	tmp_a = a;
	i = 0;
	while (len > i)
	{
		tmp_a[i] = c;
		i++;
	}
	return (a);
}
