/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:33:56 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/21 19:35:29 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	index;

	dst_len = ft_strlen(dst);
	i = 0;
	index = 0;
	if (size - 1 > dst_len && size > 0)
	{
		while (dst[index])
			index++;
		while (src[i] && i + 1 + index < size)
		{
			dst[index + i] = src[i];
			i++;
		}
		dst[index + i] = '\0';
	}
	if (size >= dst_len)
		return (ft_strlen(src) + dst_len);
	else
		return (ft_strlen(src) + size);
}
