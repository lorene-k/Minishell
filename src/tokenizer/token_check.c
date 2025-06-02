/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:28:35 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/20 15:13:36 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_not_handled(char c, char next)
{
	if (c == '&' || c == '%' || c == '\\' || c == ';' || c == '{' || c == '}'
		|| c == '[' || c == ']' || c == '*' || c == '`' || c == '('
		|| c == ')' || (c == '|' && c == next))
		return (1);
	return (0);
}

static int	check_not_handled(t_token *curr, t_infos *infos)
{
	int	i;

	i = 0;
	if (ft_isquote(curr->value[i]))
		return (0);
	while (curr->value[i])
	{
		if (ft_not_handled(curr->value[i], curr->value[i + 1]))
			return (print_parse_error(infos, 1, SYNTAX_ERR));
		i++;
	}
	return (0);
}

static int	check_syntax(t_token *curr, t_infos *infos)
{
	if (*curr->value == '|' && (!curr->prev))
		return (print_parse_error(infos, 2, SYNTAX_ERR));
	if (!curr->prev && ft_isoperator(curr->value, 0) && (!curr->next
			|| curr->next->value[0] == '&' || curr->next->value[0] == '!'
			|| curr->next->value[0] == ';' || curr->next->value[0] == '}'))
		return (print_parse_error(infos, 2, SYNTAX_ERR));
	if (ft_isoperator(curr->value, 0) && ((!curr->next || !curr->next->value)
			|| (ft_isoperator(curr->value, 0) && *curr->value != '|'
				&& ft_isoperator(curr->next->value, 0))))
		return (print_parse_error(infos, 2, SYNTAX_ERR));
	return (0);
}

int	check_invalid_tokens(t_token *token, t_infos *infos)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (check_syntax(curr, infos) || check_not_handled(curr, infos))
			return (clear_tokens(&token), 1);
		curr = curr->next;
	}
	return (0);
}
