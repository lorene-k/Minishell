/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:19:22 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/23 16:57:01 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	ft_fill_str(char *str, char const *base, char c)
{
	size_t	i;

	i = 0;
	while (base[i] != c && base[i])
	{
		str[i] = base[i];
		i++;
	}
	str[i] = '\0';
}

static int	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (-1);
}

static int	ft_fill(char **final, char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	index;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] != c && s[index + count] != '\0')
			count++;
		if (count > 0)
		{
			final[i] = malloc(sizeof(char) * (count + 1));
			if (!final[i])
				return (free_split(final));
			ft_fill_str(final[i++], (s + index), c);
			index += count;
		}
		else
			index++;
	}
	final[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**final;

	words = ft_count_words(s, c);
	final = malloc(sizeof(char *) * (words + 1));
	if (!final)
		return (NULL);
	if (ft_fill(final, s, c) == -1)
		return (NULL);
	return (final);
}
