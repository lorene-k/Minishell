/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:21:31 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 14:15:43 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_str(char **new_str, int i, int *j, char *str)
{
	if (*new_str)
		*new_str = ft_strjoin_mem(*new_str, ft_substr(str, *j, i - *j));
	else
		*new_str = ft_substr(str, *j, i - *j);
	*j = i + 1;
}

static char	*get_new_str(char *new_str, char *str, int i, int *j)
{
	char	curr_quote;

	curr_quote = '\0';
	while (str[i])
	{
		if (ft_isquote(str[i]) && curr_quote == '\0')
		{
			curr_quote = str[i];
			extract_str(&new_str, i, j, str);
		}
		else if (str[i] == curr_quote)
		{
			curr_quote = '\0';
			extract_str(&new_str, i, j, str);
		}
		i++;
	}
	return (new_str);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = NULL;
	new_str = get_new_str(new_str, str, i, &j);
	if (!new_str)
		new_str = ft_strdup(str);
	else if (str[j])
		new_str = ft_strjoin_mem(new_str, ft_substr(str, j, i - j));
	return (new_str);
}