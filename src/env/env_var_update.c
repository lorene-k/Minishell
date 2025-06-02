/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:11:35 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/13 17:22:49 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_key_with_equal(t_infos *infos, char *key)
{
	char	*temp_key;

	if (env_contains_value_on_table(infos, key) == 1)
	{
		temp_key = ft_strjoin(key, "=");
		if (!temp_key)
			return (NULL);
	}
	else
	{
		temp_key = ft_strdup(key);
		if (!temp_key)
			return (NULL);
	}
	return (temp_key);
}

static int	add_env_line(t_infos *infos, char *new_str)
{
	int		i;
	int		z;
	char	**new_envp;

	i = 0;
	while (infos->new_envp[i] != NULL)
		i++;
	z = 0;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (-1);
	while (z < i)
	{
		new_envp[z] = infos->new_envp[z];
		z++;
	}
	new_envp[z] = ft_strdup(new_str);
	if (!new_envp[z])
		return (-1);
	new_envp[++z] = NULL;
	free(infos->new_envp);
	infos->new_envp = new_envp;
	return (1);
}

static int	replace_env_line(t_infos *infos, char *key, char *new_str)
{
	int		i;
	char	*temp_key;
	int		len;

	i = 0;
	if (env_var_exists(infos, key) == 1)
	{
		temp_key = create_key_with_equal(infos, key);
		if (!temp_key)
			return (-1);
		len = ft_strlen(key);
		while (infos->new_envp[i] != NULL)
		{
			if (ft_strncmp(infos->new_envp[i], temp_key, len) == 0)
			{
				free(infos->new_envp[i]);
				infos->new_envp[i] = ft_strdup(new_str);
				if (!infos->new_envp[i])
					return (free(temp_key), -1);
				return (free(temp_key), 1);
			}
			i++;
		}
	}
	return (0);
}

static char	*create_line_env(t_infos *infos, char *key, char *value)
{
	char	*temp_str;
	char	*new_str;

	if (value != NULL || (value == NULL && env_var_exists(infos, key) == 1
			&& env_contains_value_on_table(infos, key) == 1))
	{
		temp_str = ft_strjoin(key, "=");
		if (!temp_str)
			return (NULL);
		if (value == NULL)
			new_str = ft_strjoin(temp_str, "");
		else
			new_str = ft_strjoin(temp_str, value);
		if (!new_str)
			return (NULL);
		free(temp_str);
		if (!new_str)
			return (NULL);
	}
	if ((env_var_exists(infos, key) == 1 && (value == NULL
				&& env_contains_value_on_table(infos, key) == 0))
		|| (value == NULL && env_var_exists(infos, key) == 0))
		new_str = ft_strdup(key);
	return (new_str);
}

int	add_env_var(t_infos *infos, char *key, char *value)
{
	int		ret;
	char	*new_str;

	ret = env_var_exists(infos, key);
	if (ret == -1)
		protect_memory(infos, NULL, NULL);
	if ((value == NULL && env_var_exists(infos, key) == 1
			&& env_contains_value_on_table(infos, key) == 1))
		return (0);
	new_str = create_line_env(infos, key, value);
	if (!new_str)
		protect_memory(infos, 0, 0);
	ret = replace_env_line(infos, key, new_str);
	if (ret == -1)
		protect_memory(infos, NULL, NULL);
	else if (ret == 1)
		return (free(new_str), 0);
	ret = add_env_line(infos, new_str);
	if (ret == -1)
		protect_memory(infos, NULL, NULL);
	else if (ret == 1)
		return (free(new_str), 0);
	free(new_str);
	return (0);
}
