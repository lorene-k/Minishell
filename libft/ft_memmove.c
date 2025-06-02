/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:11:36 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/23 15:20:18 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	size_t		i;

	if (!dst && !src)
		return (NULL);
	if (src >= dst)
	{
		i = 0;
		while (i < size)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		i = size;
		while (i > 0)
		{
			*(unsigned char *)(dst + i -1) = *(unsigned char *)(src + i -1);
			i--;
		}
	}
	return (dst);
}
