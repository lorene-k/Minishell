/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:31:48 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/05 17:18:59 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *line, int *i, int *j)
{
	int		opened_quote;
	char	curr_quote;

	opened_quote = 1;
	curr_quote = line[*i];
	while (line[*i + *j])
	{
		if (line[*i + *j] == curr_quote)
		{
			opened_quote = 0;
			curr_quote = '\0';
		}
		else if ((line[*i + *j] == '\'' || line[*i + *j] == '\"')
			&& !opened_quote)
		{
			opened_quote = 1;
			curr_quote = line[*i + *j];
		}
		if (!opened_quote && (ft_isspace(line[*i + *j]) || ft_isoperator(line,
					*i + *j) || line[*i + *j] == '|'))
			break ;
		(*j)++;
	}
	return (opened_quote);
}

static void	handle_quotes(char *line, int *i, t_token **token, t_infos *infos)
{
	int	j;

	j = 1;
	(*token)->error = check_quotes(line, i, &j);
	if ((*token)->error)
	{
		print_parse_error(infos, 0, QUOTE_ERR);
		return ;
	}
	if (!(*token)->value)
		(*token)->value = ft_substr(line, *i, j);
	else
		(*token)->value = ft_strjoin_mem((*token)->value, ft_substr(line, *i,
					j));
	if (!(*token)->value)
		protect_memory_tokens(infos, line, *token, 0);
	*i += j;
}

static void	get_str(char *line, int *i, t_token **token, t_infos *infos)
{
	int	j;

	j = 0;
	while (line[*i + j] && (!ft_isspace(line[*i + j])
			&& !ft_isquote(line[*i + j]) && !ft_isoperator(line, *i + j)
			&& line[*i + j] != '|'))
		j++;
	if (j == 0)
	{
		while (line[*i + j] && !ft_isspace(line[*i + j]))
			j++;
	}
	(*token)->value = ft_substr(line, *i, j);
	if (!(*token)->value)
		protect_memory_tokens(infos, line, *token, 0);
	*i += j;
}

static void	get_operator(char *line, int *i, t_token **token, t_infos *infos)
{
	int	j;

	if (ft_solo_operator(line, *i))
		j = 1;
	if (ft_multi_operator(line, *i))
		j = 2;
	(*token)->value = ft_substr(line, *i, j);
	if (!(*token)->value)
		protect_memory_tokens(infos, line, *token, 0);
	*i += j;
}

void	get_token_value(char *line, int *i, t_token **token, t_infos *infos)
{
	if ((!(ft_isquote(line[*i])) && !(ft_isoperator(line, *i)))
		|| ((line[*i] == '|' && line[*i + 1] == '|')))
		get_str(line, i, token, infos);
	if (ft_isquote(line[*i]))
		handle_quotes(line, i, token, infos);
	else if (ft_isoperator(line, *i) && !(*token)->value)
		get_operator(line, i, token, infos);
}
