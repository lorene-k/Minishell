/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:10:36 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/23 15:15:58 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;

	i = 0;
	if (!destination && !source)
		return (NULL);
	while (i < size)
	{
		*(unsigned char *)(destination + i) = *(unsigned char *)(source + i);
		i++;
	}
	return (destination);
}
