/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:44:17 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/22 18:21:08 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while ((first[i] || second[i]) && i < length)
	{
		if ((unsigned char) first[i] != (unsigned char) second[i])
			return ((unsigned char) first[i] - (unsigned char) second[i]);
		i++;
	}
	return (0);
}
