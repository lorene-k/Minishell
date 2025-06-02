/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:02:57 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/22 16:09:01 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && *(unsigned char *)(p1 + i) == *(unsigned char *)(p2 + i))
	{
		i++;
	}
	if (i < size)
		return (*(unsigned char *)(p1 + i) - *(unsigned char *)(p2 + i));
	else
		return (0);
}
