/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:24:59 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/22 15:23:06 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	size_t	i;
	char	newc;

	i = 0;
	newc = (char) searchedChar;
	while (string[i] && string[i] != newc)
	{
		i++;
	}
	if (string[i] == (char) newc)
		return ((char *) string + i);
	else
		return (NULL);
}
