/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:51:24 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/13 18:14:23 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isredirect_char(char c)
{
	if ((c == '<') || (c == '>'))
		return (1);
	return (0);
}

int	ft_solo_operator(char *line, int i)
{
	if ((line[i] && (ft_isredirect_char(line[i]) || line[i] == '|'))
		&& (!line[i + 1] || ft_isalnum(line[i + 1])
			|| ft_isspace(line[i + 1]) || ft_isquote(line[i + 1])
			|| line[i + 1] == '.' || line[i + 1] == '/'))
		return (1);
	return (0);
}

int	ft_multi_operator(char *line, int i)
{
	if ((line[i] && ft_isredirect_char(line[i]) && line[i + 1]
			&& line[i + 1] == line[i]) && (!line[i + 2]
			|| ft_isalnum(line[i + 2]) || ft_isspace(line[i + 2])
			|| line[i + 2] == '.' || line[i + 2] == '/'))
		return (1);
	return (0);
}

int	ft_isoperator(char *line, int i)
{
	if (ft_solo_operator(line, i) || ft_multi_operator(line, i))
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if ((c == '\'') || (c == '\"'))
		return (1);
	return (0);
}
