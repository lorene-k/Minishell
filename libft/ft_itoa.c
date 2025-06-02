/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:39:36 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/23 14:42:46 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_size_array(long n)
{
	size_t	size;

	size = 0;
	if (n < 0)
	{
		size = 1;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size_array;
	char	*str;
	int		is_neg;
	long	new_n;

	new_n = (long) n;
	is_neg = 0;
	size_array = ft_size_array(new_n);
	str = malloc(sizeof(char) * (size_array + 1));
	if (!str)
		return (NULL);
	if (new_n < 0)
	{
		is_neg = 1;
		new_n *= -1;
		str[0] = '-';
	}
	str[size_array] = '\0';
	while (size_array > (size_t) is_neg)
	{
		str[size_array - 1] = new_n % 10 + '0';
		new_n = new_n / 10;
		size_array--;
	}
	return (str);
}
