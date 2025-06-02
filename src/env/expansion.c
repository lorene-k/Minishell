/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:45:22 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/13 16:59:54 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_second_when_replace_one_var(t_infos *infos, char *key,
		char *first)
{
	char	*var_content;
	char	*second;

	var_content = get_env_var(infos, key);
	if (!var_content)
		return (NULL);
	second = ft_strjoin(first, var_content);
	free(var_content);
	if (!second)
		return (NULL);
	return (second);
}

static char	*first_part_replace_one_var(t_infos *infos, char *str, char *key,
		int i)
{
	char	*first;
	char	*second;
	int		ret;

	ret = 0;
	second = NULL;
	if (i == 0)
		first = ft_strdup("");
	else
		first = ft_substr(str, 0, i);
	if (!first)
		return (NULL);
	ret = env_var_exists(infos, key);
	if (ret == 1)
		second = get_second_when_replace_one_var(infos, key, first);
	else if (ret == 0)
	{
		second = ft_strjoin(first, "");
		if (!second)
			return (free(first), NULL);
	}
	else if (ret == -1)
		return (free(first), NULL);
	return (free(first), second);
}

char	*replace_one_var_on_str_from_new(t_infos *infos, char *str, char *key,
		size_t i)
{
	char	*second;
	char	*third;
	char	*final;

	second = first_part_replace_one_var(infos, str, key, i);
	if (!second)
		return (NULL);
	i++;
	while (ft_isalnum(str[i]) && i < ft_strlen(str))
		i++;
	third = ft_substr(str, i, ft_strlen(str));
	if (!third)
		return (free(second), NULL);
	final = ft_strjoin(second, third);
	if (!final)
		return (free(second), free(third), NULL);
	return (free(second), free(third), final);
}

char	*replace_str_var_new(t_infos *infos, char *str)
{
	size_t	cursor;
	char	*new_str;
	char	*tmp;

	cursor = 0;
	if (!str)
		return (NULL);
	if (!contains_env_var(str) && !contains_return_code_var(str))
		return (ft_strdup(str));
	new_str = ft_strdup(str);
	while (new_str != NULL && (contains_env_var(new_str)
			|| contains_return_code_var(new_str)))
	{
		tmp = replace_str_var_one_new(infos, new_str, 0, &cursor);
		if (!tmp)
			return (NULL);
		new_str = tmp;
		if (cursor >= ft_strlen(new_str))
			break ;
	}
	return (new_str);
}

char	*replace_str_var_heredoc_new(t_infos *infos, char *str)
{
	size_t	cursor;
	char	*new_str;
	char	*tmp;

	cursor = 0;
	if (!str)
		return (NULL);
	if (!contains_env_var(str) && !contains_return_code_var(str))
		return (ft_strdup(str));
	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	while (new_str != NULL && (contains_env_var(new_str)
			|| contains_return_code_var(new_str)))
	{
		tmp = replace_str_var_one_new(infos, new_str, 1, &cursor);
		if (!tmp)
			return (NULL);
		new_str = tmp;
		if (cursor >= ft_strlen(new_str))
			break ;
	}
	return (new_str);
}
