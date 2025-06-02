/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:53:53 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:43:52 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	protect_memory(t_infos *infos, char *str, char **tab)
{
	if (str)
		free(str);
	if (tab)
		clear_tab(tab);
	ft_putendl_fd("malloc: memory allocation failed", 2);
	free_infos_error(infos);
}

int	print_cmd_error(char *msg, t_infos *infos, int code)
{
	if (infos)
		infos->return_code = code;
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
	return (code);
}

void	print_file_error(t_cmd *cmd, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	cmd->can_access_file = 0;
}
