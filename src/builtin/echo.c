/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:59:45 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:30:46 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_infos *infos, t_cmd *cmd)
{
	int	i;
	int	contains_n;

	(void)infos;
	i = 1;
	contains_n = 0;
	if (next_is_empty(infos, cmd))
		return (0);
	if (check_builtin_error(cmd, "echo"))
		return (1);
	if (cmd->args_indexes > 2 && ft_strcmp(cmd->args[1], "-n") == 0)
		contains_n = 1;
	i += contains_n;
	while (i < cmd->args_indexes - 1)
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (i + 1 < cmd->args_indexes - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (contains_n == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
