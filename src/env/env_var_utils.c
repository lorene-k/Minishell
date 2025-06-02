/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:03:51 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/13 17:24:11 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_env_var(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '$' && i + 1 < len && (ft_isalpha(str[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

int	contains_return_code_var(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '$' && i + 1 < len && (str[i + 1] == '?'))
			return (1);
		i++;
	}
	return (0);
}

char	*get_env_var(t_infos *infos, char *key)
{
	int		i;
	char	*temp_key;
	int		len;

	i = 0;
	temp_key = ft_strjoin(key, "=");
	if (!temp_key)
		return (NULL);
	len = ft_strlen(temp_key);
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strncmp(infos->new_envp[i], temp_key, ft_strlen(temp_key)) == 0)
			return (free(temp_key), ft_substr(infos->new_envp[i], len,
					ft_strlen(infos->new_envp[i])));
		i++;
	}
	free(temp_key);
	i = 0;
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strncmp(infos->new_envp[i], key, ft_strlen(key)) == 0)
			return (ft_strdup(""));
		i++;
	}
	return (NULL);
}
