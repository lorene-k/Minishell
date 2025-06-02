/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:12:03 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/13 17:23:42 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_env_var_when_contains_value(t_infos *infos, char *key,
		char **new_envp)
{
	char	*temp_key;
	int		i;
	int		z;

	i = 0;
	z = 0;
	temp_key = ft_strjoin(key, "=");
	if (!temp_key)
		return (free(new_envp), -1);
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strncmp(infos->new_envp[i], temp_key, ft_strlen(temp_key)) == 0)
			free(infos->new_envp[i]);
		else
			new_envp[z++] = infos->new_envp[i];
		i++;
	}
	new_envp[z] = NULL;
	free(infos->new_envp);
	free(temp_key);
	infos->new_envp = new_envp;
	return (0);
}

static int	remove_env_var_when_not_contains_value(t_infos *infos, char *key,
		char **new_envp)
{
	char	*temp_key;
	int		i;
	int		z;

	i = 0;
	z = 0;
	temp_key = ft_strdup(key);
	if (!temp_key)
		return (free(new_envp), -1);
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strcmp(infos->new_envp[i], temp_key) == 0)
			free(infos->new_envp[i]);
		else
			new_envp[z++] = infos->new_envp[i];
		i++;
	}
	new_envp[z] = NULL;
	free(infos->new_envp);
	free(temp_key);
	infos->new_envp = new_envp;
	return (0);
}

int	env_var_exists(t_infos *infos, char *key)
{
	char	*temp_key;
	int		len;
	int		i;

	temp_key = ft_strjoin(key, "=");
	if (!temp_key)
		return (-1);
	len = ft_strlen(temp_key);
	i = 0;
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strncmp(infos->new_envp[i], temp_key, len) == 0)
			return (free(temp_key), 1);
		i++;
	}
	free(temp_key);
	i = 0;
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strcmp(infos->new_envp[i], key) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	env_contains_value_on_table(t_infos *infos, char *key)
{
	char	*temp_key;
	int		len;
	int		i;

	temp_key = ft_strjoin(key, "=");
	if (!temp_key)
		return (-1);
	len = ft_strlen(temp_key);
	i = 0;
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strncmp(infos->new_envp[i], temp_key, len) == 0)
		{
			free(temp_key);
			return (1);
		}
		i++;
	}
	free(temp_key);
	return (0);
}

int	remove_env_var(t_infos *infos, char *key)
{
	int		len;
	char	**new_envp;
	int		exist;

	len = 0;
	exist = env_var_exists(infos, key);
	if (exist == 0)
		return (0);
	else if (exist == -1)
		return (-1);
	while (infos->new_envp[len] != NULL)
		len++;
	new_envp = malloc(sizeof(char *) * (len));
	if (!new_envp)
		return (-1);
	if (env_contains_value_on_table(infos, key) == 1)
	{
		remove_env_var_when_contains_value(infos, key, new_envp);
		return (0);
	}
	else
	{
		remove_env_var_when_not_contains_value(infos, key, new_envp);
		return (0);
	}
}
