/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:59:45 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:30:46 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_path_null_if_nodata(t_infos *infos)
{
	char	*tmp;

	tmp = get_env_var((infos), "PATH");
	if (!tmp)
	{
		protect_memory(infos, 0, 0);
		return (-1);
	}
	if (ft_strlen(tmp) == 0)
	{
		if ((infos)->paths != NULL)
			clear_tab((infos)->paths);
		infos->paths = NULL;
		free(tmp);
		return (1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}

void	set_path_null_if_nokey(t_infos *infos)
{
	if ((infos)->paths != NULL)
		clear_tab((infos)->paths);
	infos->paths = NULL;
}

int	update_path(t_infos *infos)
{
	char	*path;

	if (env_var_exists(infos, "PATH") == 1)
	{
		if (set_path_null_if_nodata(infos) == 1)
			return (0);
		if ((infos)->paths != NULL)
			clear_tab((infos)->paths);
		path = get_env_var((infos), "PATH");
		if (!path)
		{
			(infos)->paths = NULL;
			protect_memory(infos, 0, 0);
		}
		(infos)->paths = ft_split(path, ':');
		if (!(infos)->paths)
			protect_memory(infos, path, 0);
		free(path);
	}
	else
		set_path_null_if_nokey(infos);
	return (0);
}

int	ft_export(t_infos *infos, t_cmd *cmd)
{
	int	i;
	int	not_valid_identifier;

	i = 1;
	not_valid_identifier = 0;
	if (cmd->args[1] == NULL)
	{
		print_sorted_export_env(infos);
		return (0);
	}
	else if (cmd->args_indexes >= 3)
	{
		while (i < cmd->args_indexes - 1)
		{
			not_valid_identifier = add_var_new(infos, cmd->args[i]);
			i++;
		}
		update_path(infos);
	}
	return (not_valid_identifier);
}
