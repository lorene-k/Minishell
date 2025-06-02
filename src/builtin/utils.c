/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:56:29 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 13:29:52 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_error(t_cmd *cmd, char *cmd_name)
{
	if (cmd->outfile && ft_strcmp(cmd->outfile, "/dev/full") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": write error: ", 2);
		ft_putendl_fd("No space left on device", 2);
		return (1);
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	next_is_empty(t_infos *infos, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < infos->cmd_nb)
	{
		if (infos->cmd[i] == cmd)
		{
			if (i + 1 < infos->cmd_nb)
			{
				if (infos->cmd[i + 1]->is_empty)
					return (1);
			}
		}
		i++;
	}
	return (0);
}
