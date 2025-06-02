/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:39:29 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/12 14:40:18 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_infos *infos, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->args_indexes > 2)
	{
		while (i < cmd->args_indexes - 1)
		{
			remove_env_var(infos, cmd->args[i]);
			i++;
		}
	}
	update_path(infos);
	return (0);
}
