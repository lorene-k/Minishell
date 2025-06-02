/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:52:39 by imounjed          #+#    #+#             */
/*   Updated: 2024/09/19 14:52:44 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>

static void	rename_one_cmd(t_cmd *cmd, t_infos **infos)
{
	char	*temp;

	if (ft_strchr(cmd->args[0], '/'))
	{
		temp = ft_strdup(ft_strrchr(cmd->args[0], '/') + 1);
		if (!temp)
			protect_memory(*infos, 0, 0);
		cmd->args[0] = temp;
	}
}

int	is_dir(t_cmd *cmd)
{
	struct stat	buf;

	if (ft_strchr(cmd->args[0], '/'))
	{
		stat(cmd->args[0], &buf);
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	else
	{
		return (0);
	}
	return (0);
}

int	file_or_directory_exists(t_cmd *cmd)
{
	struct stat	buf;
	int			ret;

	if (ft_strchr(cmd->args[0], '/'))
	{
		ret = stat(cmd->args[0], &buf);
		if (ret < 0)
			return (0);
	}
	return (1);
}

void	check_and_assign_path(t_cmd *actual_cmd, t_infos **infos)
{
	if (file_or_directory_exists(actual_cmd))
	{
		if (is_dir(actual_cmd))
			actual_cmd->cmd_not_found = 3;
		else
		{
			actual_cmd->path = command_path_parsing(infos, actual_cmd->args[0]);
			if (!(actual_cmd->path))
			{
				if (errno == EACCES)
					actual_cmd->cmd_not_found = 2;
				else
					actual_cmd->cmd_not_found = 1;
			}
			rename_one_cmd(actual_cmd, infos);
		}
	}
	else
	{
		actual_cmd->cmd_not_found = 4;
	}
}

int	set_all_cmd_path(t_infos **infos)
{
	t_cmd	*actual_cmd;
	int		i;

	i = 0;
	while (i < (*infos)->cmd_nb)
	{
		actual_cmd = (*infos)->cmd[i];
		actual_cmd->cmd_not_found = 0;
		if (!actual_cmd->is_empty)
		{
			if (!is_builtin(actual_cmd->args[0]))
			{
				check_and_assign_path(actual_cmd, infos);
			}
		}
		i++;
	}
	return ((*infos)->return_code);
}
