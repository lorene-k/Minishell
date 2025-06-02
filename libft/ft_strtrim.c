/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:53:32 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/22 16:29:05 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contains_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*new;
	size_t	start;
	size_t	end;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_contains_set(s1[start], set))
		start++;
	while (end > start && ft_contains_set(s1[end - 1], set))
		end--;
	new = malloc(sizeof(char) * (end - start + 1));
	if (!new)
		return (NULL);
	while (start < end)
	{
		new[i] = s1[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
