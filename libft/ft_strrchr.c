/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:49:01 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/23 14:58:09 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	long	size;
	char	newc;

	size = 0;
	newc = (char) searchedChar;
	size = ft_strlen(string);
	while (size >= 0)
	{
		if (string[size] == newc)
		{
			return ((char *) &string[size]);
		}
		size--;
	}
	return (NULL);
}
