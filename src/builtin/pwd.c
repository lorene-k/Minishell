/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:36:49 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/20 14:37:37 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_infos *infos, t_cmd *cmd)
{
	char	buffer[PATH_MAX];

	(void)infos;
	if (next_is_empty(infos, cmd))
		return (0);
	if (check_builtin_error(cmd, "pwd"))
		return (1);
	if (!getcwd(buffer, sizeof(buffer)))
	{
		ft_putstr_fd("getcwd : failed to allocate buffer", 2);
		exit(1);
	}
	else
	{
		add_env_var(infos, "PWD", buffer);
		ft_putendl_fd(buffer, 1);
		return (0);
	}
}
