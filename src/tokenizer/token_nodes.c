/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:39:11 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/01 16:39:52 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_first_node(t_token *token)
{
	t_token	*first;

	if (!token)
		return (0);
	first = token;
	while (first->prev)
		first = first->prev;
	return (first);
}

void	clear_tokens(t_token **start)
{
	t_token	*current;
	t_token	*next;

	if (!start || !*start)
		return ;
	current = get_first_node(*start);
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*start = NULL;
}

static void	init_token(t_token **token)
{
	(*token)->value = NULL;
	(*token)->len = 0;
	(*token)->s_quote = 0;
	(*token)->error = 0;
	(*token)->next = NULL;
	(*token)->prev = NULL;
}

int	add_token_node(t_token **current)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	init_token(&token);
	if (!*current)
		*current = token;
	else
	{
		(*current)->next = token;
		token->prev = *current;
		*current = token;
	}
	return (1);
}
