/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:25:55 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 14:36:21 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_all_cmd_args(t_infos **infos)
{
	int		i;
	t_cmd	*actual_cmd;

	i = 0;
	while (i < (*infos)->cmd_nb)
	{
		actual_cmd = (*infos)->cmd[i];
		if (modify_args_cmd(actual_cmd, *infos) == -1)
			protect_memory(*infos, NULL, NULL);
		i++;
	}
}

int	get_cmd_id(t_infos *infos, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < infos->cmd_nb)
	{
		if (cmd == infos->cmd[i])
			return (i);
		i++;
	}
	return (-1);
}

static t_cmd	*get_cmd_memory(int args_n)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc(sizeof(char *), (args_n + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->args_indexes = (args_n + 1);
	return (cmd);
}

t_cmd	*get_cmd(int args_n, char **cmd_array, int last_index, t_infos **infos)
{
	t_cmd	*cmd;
	int		i;
	int		z;

	z = 0;
	i = 0;
	cmd = get_cmd_memory(args_n);
	if (!cmd)
		protect_memory(*infos, 0, 0);
	while (z < (args_n))
	{
		cmd->args[z] = ft_strdup(cmd_array[last_index + z]);
		if (!cmd->args[z])
			return (protect_cmd_memory(i, z, &cmd), NULL);
		z++;
	}
	cmd->args[z] = NULL;
	return (cmd);
}

void	set_default_cmd_values(t_infos **infos)
{
	int		i;
	t_cmd	*actual_cmd;

	i = 0;
	while (i < (*infos)->cmd_nb)
	{
		actual_cmd = (*infos)->cmd[i];
		actual_cmd->intype = NORMAL;
		actual_cmd->outtype = NORMAL;
		i++;
	}
}
