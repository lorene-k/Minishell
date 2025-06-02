/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:48:26 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 13:41:35 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*store_token(t_token *curr)
{
	char	*str;

	if (!curr->value)
		return (NULL);
	str = malloc(sizeof(char) * curr->len + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strlcpy(str, curr->value, curr->len + 1);
	return (str);
}

static char	**token_to_str(t_token **token, int n_nodes, t_infos *infos)
{
	int		i;
	char	**token_tab;
	t_token	*curr;

	i = -1;
	curr = *token;
	token_tab = malloc(sizeof(char *) * (n_nodes + 1));
	if (!token_tab)
		protect_memory_tokens(infos, 0, *token, 0);
	token_tab[n_nodes] = NULL;
	while (curr)
	{
		token_tab[++i] = store_token(curr);
		if (!token_tab[i] && curr->value)
			protect_memory_tokens(infos, 0, *token, token_tab);
		else if (!token_tab[i] && !curr->value)
			i--;
		curr = curr->next;
	}
	clear_tokens(token);
	return (token_tab);
}

static t_token	*create_tokens(char *line, t_infos *infos, int *n_nodes)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	(void)infos;
	while (i < (int)ft_strlen(line))
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '#' || !line[i])
			break ;
		*n_nodes += add_token_node(&token);
		if (!token)
			protect_memory_tokens(infos, 0, token, 0);
		get_token_value(line, &i, &token, infos);
		if (token->error)
			return (clear_tokens(&token), NULL);
		token->len = ft_strlen(token->value);
		if (!token->value)
			n_nodes--;
	}
	return (get_first_node(token));
}

char	**generate_tokens_array(char *line, t_infos *infos)
{
	int		n_nodes;
	t_token	*token;

	n_nodes = 0;
	token = NULL;
	token = create_tokens(line, infos, &n_nodes);
	if (!token || check_invalid_tokens(token, infos))
		return (NULL);
	return (token_to_str(&token, n_nodes, infos));
}
