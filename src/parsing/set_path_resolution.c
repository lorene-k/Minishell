/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:32 by imounjed          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:14 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in_out_pipes_and_normal(t_infos **infos)
{
	int		i;
	t_cmd	*actual_cmd;

	i = 0;
	if ((*infos)->pipes_nb >= 1)
	{
		while (i < (*infos)->cmd_nb)
		{
			actual_cmd = (*infos)->cmd[i];
			if (actual_cmd->outtype == NORMAL && i + 1 < (*infos)->cmd_nb)
			{
				if ((*infos)->cmd[i + 1]->intype == NORMAL)
				{
					actual_cmd->outtype = PIPE;
					(*infos)->cmd[i + 1]->intype = PIPE;
				}
				else if (((*infos)->cmd[i + 1]->intype == HEREDOC)
					|| ((*infos)->cmd[i + 1]->intype == FILE_REAL))
					actual_cmd->outtype = PIPE;
			}
			i++;
		}
	}
}

char	*absolute_path(t_infos **infos, char **all_paths, char *cmd)
{
	char	*temp;
	char	*actual_command;

	while (*all_paths)
	{
		temp = ft_strjoin(*all_paths, "/");
		if (!temp)
			return (free_infos_error(*infos), NULL);
		actual_command = ft_strjoin(temp, cmd);
		free(temp);
		if (!actual_command)
			return (free_infos_error(*infos), NULL);
		if (access(actual_command, F_OK | X_OK) == 0)
			return (actual_command);
		free(actual_command);
		all_paths++;
	}
	return (NULL);
}

char	*command_path_parsing(t_infos **infos, char *cmd)
{
	char	**all_paths;

	all_paths = (*infos)->paths;
	if (env_var_exists(*infos, "PATH") == 0)
		return (NULL);
	if (!all_paths)
		return (NULL);
	if ((ft_strlen(cmd) > 2 && cmd[0] == '.' && cmd[1] == '/')
		|| (ft_strlen(cmd) > 1 && cmd[0] == '/') || (ft_strlen(cmd) > 2
			&& ft_strchr(cmd, '/') != NULL))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		if (errno == EACCES)
			return (NULL);
	}
	return (absolute_path(infos, all_paths, cmd));
}
