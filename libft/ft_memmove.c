/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:50:00 by samin             #+#    #+#             */
/*   Updated: 2020/11/10 01:54:14 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == NULL && src == NULL)
		return (0);
	if (dst <= src)
	{
		tmp_dst = dst;
		tmp_src = (unsigned char *)src;
		while (len--)
			*tmp_dst++ = *tmp_src++;
	}
	else
	{
		tmp_dst = dst;
		tmp_dst += len;
		tmp_src = (unsigned char *)src;
		tmp_src += len;
		while (len--)
			*--tmp_dst = *--tmp_src;
	}
	return (dst);
}
