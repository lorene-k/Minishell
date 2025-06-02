/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:59:45 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:30:46 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_infos *infos, t_cmd *cmd)
{
	int	i;

	if (next_is_empty(infos, cmd))
		return (0);
	i = 0;
	if (check_builtin_error(cmd, "env"))
		return (1);
	if (cmd->args_indexes > 2)
		return (print_cmd_error("env: too many arguments", infos, 125));
	while (infos->new_envp[i] != NULL)
	{
		if (ft_strchr(infos->new_envp[i], '=') != NULL)
			ft_putendl_fd(infos->new_envp[i], 1);
		i++;
	}
	return (0);
}
