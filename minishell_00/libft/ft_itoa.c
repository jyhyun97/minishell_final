/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:43:04 by samin             #+#    #+#             */
/*   Updated: 2020/11/03 02:52:53 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*number_excption(char *num, long n, int len)
{
	if (n == 0)
	{
		ft_strlcpy(num, "0", len + 1);
		return (num);
	}
	if (n == -2147483648)
	{
		ft_strlcpy(num, "-2147483648", len + 1);
		return (num);
	}
	return (NULL);
}

int		number_len(long n)
{
	int i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;

	len = number_len(n);
	if (!(num = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n == 0 || n == -2147483648)
		num = number_excption(num, n, len);
	num[len--] = '\0';
	if (n < 0)
	{
		num[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		num[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (num);
}
