/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:21 by imounjed          #+#    #+#             */
/*   Updated: 2024/09/19 14:53:23 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	resize_args_cmd(t_cmd *cmd, int new_args_indexes)
{
	int		i;
	int		z;
	char	**new_args;

	i = 0;
	z = 0;
	new_args = ft_calloc(sizeof(char *), (new_args_indexes));
	if (!new_args)
		return (-1);
	while (i < cmd->args_indexes)
	{
		if (cmd->args[i] != NULL)
		{
			new_args[z] = cmd->args[i];
			z++;
		}
		i++;
	}
	new_args[new_args_indexes - 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	cmd->args_indexes = new_args_indexes;
	return (0);
}

int	modify_one_arg_cmd(t_cmd *cmd, t_infos *infos, int *new_args_indexes, int i)
{
	char	*actual_arg;

	actual_arg = replace_str_var_new(infos, cmd->args[i]);
	if (!actual_arg)
		return (-1);
	free(cmd->args[i]);
	cmd->args[i] = actual_arg;
	if (ft_strcmp(actual_arg, "") == 0)
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
		*new_args_indexes = *new_args_indexes - 1;
	}
	else
	{
		actual_arg = remove_quotes(cmd->args[i]);
		if (!actual_arg)
			return (-1);
		free(cmd->args[i]);
		cmd->args[i] = actual_arg;
	}
	return (0);
}

int	modify_args_cmd(t_cmd *cmd, t_infos *infos)
{
	int		i;
	int		new_args_indexes;

	i = 0;
	new_args_indexes = cmd->args_indexes;
	while (i < cmd->args_indexes - 1 && cmd->args[i] != NULL)
	{
		modify_one_arg_cmd(cmd, infos, &new_args_indexes, i);
		i++;
	}
	return (resize_args_cmd(cmd, new_args_indexes));
	return (0);
}
